/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: enem1ai.cpp
Purpose: adds enemy behaviour provides different configuration possibilities
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 16th October 2017
---------------------------------------------------------*/




#include "enemy1AI.h"
#include "bodycomponent.h"
#include "gameobject.h"
#include "gameobjectmanager.h"
#include "../maths/math2D.h"
#include "../enginelogger/enginelogger.h"
#include "weaponcomponent.h"
#include "../event/eventmanager.h"
#include "../event/event.h"

namespace enginecore {

	namespace component {


		Enemy1AI::Enemy1AI() {


			is_air_borne_ = false;
			body_component_ = nullptr;
			dir_ = 1;
			counter_ = 0;
			fire_speed_ = 1.0;
			can_shoot_ = true;
			state_ = E_NONE;
			prev_state_ = E_NONE;
			sensor_range_x_ = 100;
			sensor_range_y_ = 100;
			target_ = nullptr;
			target_name_ = "";
			weapon_ = nullptr;
		}
		
		void Enemy1AI::Update() {
			
			if (!active_) {

				return;
			}

			if (!target_) {

				target_ = GameobjectManager::GetInstance()->GetGameObjectByTag(target_name_);
			}

			CheckForTarget();
			Behave();
		}


		void Enemy1AI::CheckForTarget() {

			if (!can_shoot_ || !target_) {

				return;
			}
			if (math::StaticRectToStaticRect(&target_->get_position(), target_->get_width(), target_->get_height(), &owner_->get_position(), owner_->get_width()*sensor_range_x_, owner_->get_height()*sensor_range_y_)) {

				prev_state_ = state_;
				state_ = E_ATTACK;
			//	ENGINE_LOG("Playaer Targeted");
			}
			else {

				if (state_ == E_ATTACK) {
					prev_state_ = E_ATTACK;
					state_ = E_WALK;
				}
			}
			
		}

		void Enemy1AI::Behave() {

			
			switch (state_) {
				
			case E_ATTACK:
				Attack();
				break;

			case E_WALK:
				Walk();
				break;

			case E_IDLE:
				Stop();
				break;

			case E_JUMP:
				Attack();
				break;

			case E_RETRIEVE:
				Retrieve();
				break;
			case E_WAIT:
				break;

			}
		}

		void Enemy1AI::Detach() {

			if (is_air_borne_) {
			
				body_component_->set_velocityX(0.0f);
				body_component_->set_velocityY(0.0f);
				body_component_->set_mass(40.0f);
				body_component_->set_gravity_scale(1.0f);
				body_component_->set_type(physics::E_BODY_TYPE_DYNAMIC);
				body_component_->UpdateMass();
	
			}
		}

		void Enemy1AI::Reset() {

			is_air_borne_ = false;
			can_shoot_ = true;
			fire_speed_ = 1.0f;
			body_component_ = nullptr;
			dir_ = 1;
			counter_ = 0;
			state_ = E_NONE; 
			prev_state_ = E_NONE;
			sensor_range_x_ = 100;
			sensor_range_y_ = 100;
			target_ = nullptr;
			target_name_ = "";
			weapon_ = nullptr;
			events::EventManager::GetInstance()->UnscribeThisComponent(events::E_EVENT_ENABLE_SHOOT, this);
		}
		
		void Enemy1AI::Init(GameObject* owner) {

			owner_ = owner;
			events::EventManager::GetInstance()->SubscribeComponentToEvent(events::E_EVENT_ENABLE_SHOOT, this);
		}
		
		void Enemy1AI::UpdateProperties() {

			body_component_ = static_cast<BodyComponent*>( owner_->GetComponent(E_COMPONENT_TYPE_BODY));
			state_ = E_WALK;
		}

		void Enemy1AI::HandleEvent(events::Event *event) {

			if (event->get_type() == events::E_EVENT_ENABLE_SHOOT && event->get_object_id() == get_id()) {

				can_shoot_ = true;
				state_ = E_ATTACK;
			}
		
		}

		//Ai bhaviour related

		void Enemy1AI::Stop() {

			if (++counter_ < max_idle_) {

				body_component_->set_velocityX(0.0f);
			}
			else {

				counter_ = 0;
				dir_ *= -1;
				state_ = E_WALK;
				owner_->FlipX();
			}
		}

		void Enemy1AI::Walk() {
			if (is_air_borne_) {

				return;
			}

			if (++counter_ < stroll_limit_) {
				
				if (abs(body_component_->get_velocity().x_) <= owner_->get_max_speed()) {

					body_component_->ApplyForceX(owner_->get_move_force()*dir_);
				}
			}
			else {
				counter_ = 0;
				state_ = E_IDLE;
			}

		}
		
		void Enemy1AI::Jump() {


		}

		void Enemy1AI::Attack() {

			
			AimPlayer();
			//if (can_shoot_) {

			//	ENGINE_LOG("Attack");
			/*	can_shoot_ = false;
				events::Event *es = new events::Event();
				es->set_type(events::E_EVENT_ENABLE_SHOOT);
				es->set_object_id(get_id());
				es->set_time(fire_speed_);
				events::EventManager::GetInstance()->AddTimedEvent(es);
				state_ = E_WAIT;
			}*/
				Shoot();
		
		}


		void Enemy1AI::AimPlayer() {
			if (owner_->get_position_x() > target_->get_position_x()) {

				owner_->SetFlipX(-1.0f);
			}
			else {

				owner_->SetFlipX(1.0f);
			}
			weapon_->Aim(target_->get_position_x(), target_->get_position_y(), owner_->get_position_x(), owner_->get_position_y());
		}

		void Enemy1AI::Shoot() {


			weapon_->Fire(target_->get_position_x(), target_->get_position_y()+target_->get_height()*.5f);
		}

		void Enemy1AI::Retrieve() {


		}


	}
}
