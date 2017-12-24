
/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: bodycomponent.cpp
Purpose: body component for gameobject
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 16th October 2017
---------------------------------------------------------*/


#include "bodycomponent.h"
#include "../physics/physicsmanager.h"
#include "gameobject.h"
#include "../event/event.h"
#include "../event/eventmanager.h"
#ifdef TEST_MODE
#include "../enginelogger/enginelogger.h"
#include "../common/scenemanager.h"
#endif

#include "shapecomponent.h"


namespace enginecore {


	namespace component {

		BodyComponent::BodyComponent() {
			
			math::Vector2DSet(&force_, 0.0f, 0.0f);
			math::Vector2DSet(&position_, 0.0f, 0.0f);
			math::Vector2DSet(&velocity_, 0.0f, 0.0f);
			math::Vector2DSet(&acceleration_, 0.0f, 0.0f);
			math::Vector2DSet(&prev_position_, 0.0f, 0.0f);
			mass_ = 0.0f;
			type_ = physics::E_BODY_TYPE_STATIC;
			owner_ = nullptr;
			inverse_mass_ = 0.0;
			gravity_scale_ = 1.0;
			collision_tag_ = 0;
			shape_component_ = nullptr;
			friction_ = 0.99f;
			once_ = false;
			is_physics_on_ = false;
			is_bullet_  = false;
		}
	
		void BodyComponent::ResetForces() {

			math::Vector2DSet(&force_, 0.0f, 0.0f);
		}

		void BodyComponent::ResetBody() {

			math::Vector2DSet(&force_, 0.0f, 0.0f);
			math::Vector2DSet(&position_, 0.0f, 0.0f);
			math::Vector2DSet(&velocity_, 0.0f, 0.0f);
			math::Vector2DSet(&acceleration_, 0.0f, 0.0f);
			math::Vector2DSet(&prev_position_, 0.0f, 0.0f);
		}

		void BodyComponent::Update() {
			

		}

		void BodyComponent::UpdateMass() {

			if (mass_) {

				inverse_mass_ = 1.0f / mass_;
			}
			else {

				inverse_mass_ = 0.0f;
			}
		}

		void BodyComponent:: ApplyForceX(float force_x) {


			force_.x_ += force_x*enginecore::EngineConfig::config_->ptm_;
		}


		void BodyComponent::ApplyForceY(float force_y) {

			force_.y_ += force_y*enginecore::EngineConfig::config_->ptm_;
		}


		void BodyComponent::Integerate(float dt) {

			//dt = (float) 0.01667f;
			//calculate force

			if (!is_physics_on_ || !active_) {

			
				return;
			}


			if (owner_->get_tag() == "animatedai") {

				int i = 0;
			}

			force_.y_ -= physics::PhysicsManager::GetInstance()->get_gravity();

			force_.y_ = type_ == physics::E_BODY_TYPE_KINEMATIC ? 0.0f : force_.y_;
			friction_ = type_ == physics::E_BODY_TYPE_KINEMATIC ? 1.0f : friction_;//maintains speed for kinetmatic bodies


			//calculate acceleration
			acceleration_.x_ = force_.x_ * inverse_mass_ * gravity_scale_;
			acceleration_.y_ = force_.y_ * inverse_mass_ * gravity_scale_;

			//calculate velcoty

			velocity_.x_ = acceleration_.x_*dt + velocity_.x_;
			velocity_.y_ = acceleration_.y_*dt + velocity_.y_;

			//store previous position
			math::Vector2DSet(&prev_position_ ,position_.x_,position_.y_) ;

			//FRICTION 
			math::Vector2DScale(&velocity_, &velocity_, friction_);
			velocity_.x_ *= friction_;
		//	velocity_.x_ *= .8f;
			//velocity_.y_ *= friction_;

			//change position
			math::Vector2DScaleAdd(&position_, &velocity_, &prev_position_, dt);

			//update position
		//	owner_->SetPosition(position_);

			//clear forces
			math::Vector2DSet(&force_, 0.0f, 0.0f);

		}

		void BodyComponent::UpdatePosition() {

			if (!active_) {
				return;
			}
			//update position
			if (owner_->get_parent()) {
				
			 	owner_->SetPosition(owner_->get_parent()->get_position());
			}
			else {

				owner_->SetPosition(position_);
			}
		
		}

		void BodyComponent::Init(GameObject* owner) {
			
			owner_ = owner;

			if (type_ == physics::E_BODY_TYPE_STATIC) {

				mass_ = 0.0f;
			}

			UpdateMass();

			/*if no gravity don't apply friction*/
			if (!gravity_scale_) {
				friction_ = 1.0f;
			}
		}


		void BodyComponent::HandleEvent(events::Event* event) {

			if (!active_) {
				return;
			}

			if (event->get_type() == events::E_EVENT_COLLISION) {

				events::Event *ev = event;

				if (ev->get_body1()->get_owner()->get_tag() == "player" && ev->get_body2()->get_owner()->get_tag() == "gun") {

  					events::Event player_hit;
					player_hit.set_type(events::E_EVENT_PLAYERHIT);
					player_hit.set_player(owner_);
					player_hit.set_other(ev->get_body2()->get_owner());
					events::EventManager::GetInstance()->SendEvent(&player_hit);

				}

				else if (ev->get_body1()->get_owner()->get_tag() == "player" && ev->get_body2()->get_owner()->get_tag() == "next_level") {

					events::Event next_level;
					next_level.set_type(events::E_NEXT_LEVEL);
					events::EventManager::GetInstance()->SendEvent(&next_level);

				}
				else if (ev->get_body1()->get_owner()->get_tag() == "bullet" ) {
					if (ev->get_body2()->get_owner()->get_tag() == "player" || ev->get_body2()->get_owner()->get_tag() == "gun") {

					}
					else {

						events::Event bullet_hit;
						bullet_hit.set_type(events::E_EVENT_BULLETHIT);
						bullet_hit.set_bullet(ev->get_body1()->get_owner());
						bullet_hit.set_other(ev->get_body2()->get_owner());
						events::EventManager::GetInstance()->SendEvent(&bullet_hit);
					}

					
				}
				else if (ev->get_body1()->get_owner()->get_tag() == "enemybullet") {
					if (ev->get_body2()->get_owner()->get_tag() == "enemy" || ev->get_body2()->get_owner()->get_tag() == "enemygun") {

					}
					else {

						
						events::Event bullet_hit;
						bullet_hit.set_type(events::E_EVENT_BULLETHIT);
						bullet_hit.set_bullet(ev->get_body1()->get_owner());
						bullet_hit.set_other(ev->get_body2()->get_owner());
     					events::EventManager::GetInstance()->SendEvent(&bullet_hit);
					}

				}
				else if(ev->get_body1()->get_owner()->get_tag() == "missile") {

					if (ev->get_body2()->get_owner()->get_tag() == "player" || ev->get_body2()->get_owner()->get_tag() == "gun") {

					}
					else {

						events::Event missile_hit;
						missile_hit.set_type(events::E_EVENT_MISSILE_HIT);
						missile_hit.set_missile(ev->get_body1()->get_owner());
						missile_hit.set_other(ev->get_body2()->get_owner());
						events::EventManager::GetInstance()->SendEvent(&missile_hit);
					}

				}

				else if (ev->get_body1()->get_owner()->get_tag() == "enemymissile" || ev->get_body1()->get_owner()->get_tag() == "enemyboss") {

					if (ev->get_body1()->get_owner()->get_tag() == "enemymissile" || ev->get_body2()->get_owner()->get_tag() == "enemy"  || ev->get_body2()->get_owner()->get_tag() == "boss" || ev->get_body2()->get_owner()->get_tag() == "enemygun") {

					}
					else {

						events::Event missile_hit;
						missile_hit.set_type(events::E_EVENT_MISSILE_HIT);
						missile_hit.set_missile(ev->get_body1()->get_owner());
						missile_hit.set_other(ev->get_body2()->get_owner());
						events::EventManager::GetInstance()->SendEvent(&missile_hit);
					}

				}




#ifdef TEST_MODE
			//	ENGINE_LOG("This is body1 in colliding : %s ", ev->get_body1()->get_owner()->get_tag().c_str());
				//ENGINE_LOG("This is body2 in colliding : %s ", ev->get_body2()->get_owner()->get_tag().c_str());

#endif
			}

		}


		BodyComponent::~BodyComponent() {

			Reset();
		}

		void BodyComponent:: Reset() {

			is_bullet_ = false;
			active_ = false;
			is_physics_on_ = false;
			once_ = false;
			math::Vector2DSet(&force_, 0.0f, 0.0f);
			math::Vector2DSet(&position_, 0.0f, 0.0f);
			math::Vector2DSet(&velocity_, 0.0f, 0.0f);
			math::Vector2DSet(&acceleration_, 0.0f, 0.0f);
			math::Vector2DSet(&prev_position_, 0.0f, 0.0f);
			mass_ = 0.0f;
			type_ = physics::E_BODY_TYPE_STATIC;
			owner_ = nullptr;
			inverse_mass_ = 0.0;
			gravity_scale_ = 1.0f;
			collision_tag_ = 0;
			shape_component_ = nullptr;

		}

	}
}