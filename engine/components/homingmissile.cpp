/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: hommingmissile.cpp
Purpose: homing behaviour for the missiles
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 16th October 2017
---------------------------------------------------------*/


#include "homingmissile.h"
#include "../maths/vector2D.h"
#include "../maths/matrix2D.h"
#include "../fpscontroller/fpscontroller.h"
#include "gameobject.h"
#include "bodycomponent.h"
#include "transformcomponent.h"
#include "gameobjectmanager.h"
#include "../maths/math-common.h"
#include "../event/eventmanager.h"
#include "../particlemanager/particlemanager.h"


namespace enginecore {

	namespace component {

		HomingMissile::HomingMissile() {

			rotation_speed_ = (float) M_PI / 2.0f;
			speed_ = 150.0f;


			body_component_  = nullptr;
			transform_ = nullptr;

			is_destroyed_ = false;
			damage_ = 10;
			
			target_ = nullptr;
			owner_ = nullptr;
		}


		HomingMissile::~HomingMissile() {

			Reset();
		}


		void HomingMissile::Update() {

			if (!active_ ) {

				return;
			}


			if (!target_) {

				target_ = GameobjectManager::GetInstance()->GetGameObjectByTag(target_name_);
			}

			if (!target_) {

				return;
			}

			math::Vector2D target_vector;

			math::Vector2DSub(&target_vector, &target_->get_position(), &transform_->get_position());
			math::Vector2DNormalize(&target_vector, &target_vector);

			float dotresult = math::Vector2DDotProduct(&target_vector, &body_component_->get_velocity());
			float angleDeg = acosf(dotresult);
			float angleRad = maths::ConvertToRadians(angleDeg);

			math::Matrix2D rot;
			math::Vector2D normal;

			math::Matrix2DRotDeg(&rot, 90.0f);
			math::Matrix2DMultVec(&normal, &rot, &body_component_->get_velocity());


			float turn = math::Vector2DDotProduct(&normal, &target_vector);

			if (turn > 0) {

				if (angleRad < rotation_speed_)
					transform_->SetRotation( angleDeg);// ->mpComponent_Transform->mAngle += angle;
				else
					transform_->SetRotation(transform_->get_rotation() +maths::ConvertToDegrees( rotation_speed_*fps::FpsController::GetInstance()->get_dt())); //pInst->mpComponent_Transform->mAngle += rotation_speed_*fps::FpsController::GetInstance()->get_dt();
			}
			else {

				if (angleRad < rotation_speed_)
					transform_->SetRotation( angleDeg); //pInst->mpComponent_Transform->mAngle -= angle;
				else
					transform_->SetRotation(transform_->get_rotation() - maths::ConvertToDegrees( rotation_speed_*fps::FpsController::GetInstance()->get_dt())); // pInst->mpComponent_Transform->mAngle -= rotation_speed_*fps::FpsController::GetInstance()->get_dt();

			}

			math::Vector2D vel;
			math::Vector2DSet(&vel, body_component_->get_velocity().x_, body_component_->get_velocity().y_);
			math::Vector2DFromAngleDeg(&vel, transform_->get_rotation());
			math::Vector2DScale(&vel, &vel, speed_);
			body_component_->set_velocity(vel);
		}

		void HomingMissile::Reset() {

			if (body_component_) {

				body_component_->ResetBody();
			}
			is_destroyed_ = false;
			rotation_speed_ = (float)M_PI / 2.0f;
			speed_ = 250.0f;
			body_component_ = nullptr;
			transform_ = nullptr;

			is_destroyed_ = false;
			damage_ = 10;
			owner_ = nullptr;
			target_ = nullptr;

			events::EventManager::GetInstance()->UnscribeThisComponent(events::E_EVENT_MISSILE_HIT, this);

		}

		void HomingMissile::Init(GameObject* owner) {

			owner_ = owner;
			
		}

		void HomingMissile::HandleEvent(events::Event *event) {

			if (event->get_type() == events::E_EVENT_MISSILE_HIT) {

				events::Event* missile_event = (event);
				if (missile_event->get_missile()->get_id() == owner_->get_id()) {

					particlesystem::ParticleManager::GetInstance()->GenerateParticle(body_component_->get_position().x_, body_component_->get_position().y_, 5, -10, 10, 1.0, 1.0, 0.0);
					events::Event healthhit;
					healthhit.set_type(events::E_EVENT_HEALTH_HIT);
					healthhit.set_damage(damage_);
					healthhit.set_other(missile_event->get_other());
					events::EventManager::GetInstance()->SendEvent(&healthhit);
					DestroySelf();

				}
			}
		}


		void HomingMissile::Fired(float start_x, float start_y) {

			is_destroyed_ = false;
			owner_->SetPositionX(start_x);
			owner_->SetPositionY(start_y);

			body_component_->set_positionX(start_x);
			body_component_->set_positionY(start_y);

			body_component_->set_is_physics_on(true);
			owner_->SetActive(true);


			events::EventManager::GetInstance()->SubscribeComponentToEvent(events::E_EVENT_MISSILE_HIT, this);
		}

		void HomingMissile::UpdateProperties() {

			BodyComponent* body = static_cast<BodyComponent*>(owner_->GetComponent(E_COMPONENT_TYPE_BODY));

			if (body) {

				body_component_ = body;
			}

			TransformComponent* transform = static_cast<TransformComponent*>(owner_->GetComponent(E_COMPONENT_TYPE_TRANSFORM));

			if (transform) {

				transform_ = transform;
			}

		}



		void HomingMissile::DestroySelf() {

			if (is_destroyed_) {

				return;
			}
	
			events::EventManager::GetInstance()->UnscribeThisComponent(events::E_EVENT_MISSILE_HIT, this);

			is_destroyed_ = true;
			owner_->SetPositionX(-100);
			owner_->SetPositionY(-100);
			body_component_->set_positionX(-100);
			body_component_->set_positionY(-100);
			body_component_->ResetBody();
			body_component_->set_is_physics_on(false);
			owner_->SetActive(false);
			//	ENGINE_LOG("Bullet Destroyed : %d", get_id());

		}
	}
}