/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: bulletcomponent.cpp
Purpose: bullet behaviour component
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 16th October 2017
---------------------------------------------------------*/



#include "bulletcomponent.h"
#include "gameobject.h"
#include "../maths/math-common.h"
#include "bodycomponent.h"
#include "../event/eventmanager.h"
#include "../event/event.h"
#include "../enginelogger/enginelogger.h"
#include "../particlemanager/particlemanager.h"

namespace enginecore {

	namespace component {

		class ComponentManager;
		class ObjectFactory;

		void BulletComponent::Update() {


		}
		
		void BulletComponent::Init(GameObject* owner) {

			owner_ = owner;
			
		}

		BulletComponent::BulletComponent() {

			is_destroyed_ = false;
			owner_ = nullptr;
			damage_ = 0;
			time_out_ = 0.0f;
		}
		
		BulletComponent::~BulletComponent() {

			Reset();
		}


		void BulletComponent::UpdateProperties() {

			BodyComponent* body = static_cast<BodyComponent*>(owner_->GetComponent(E_COMPONENT_TYPE_BODY));

			if (body) {

				body_ = body;
			}
		}
		
		void BulletComponent::Reset() {

			is_destroyed_ = false;
			active_ = false;
			owner_ = nullptr;
			damage_ = 0;
			time_out_ = 0.0f;
			
			events::EventManager::GetInstance()->UnscribeThisComponent(events::E_EVENT_DISABLE_OBJECT, this);
			events::EventManager::GetInstance()->UnscribeThisComponent(events::E_EVENT_BULLETHIT, this);
		}

		void BulletComponent::Fired(float click_x , float click_y , float speed_ , float start_posx , float start_posy) {


			is_destroyed_ = false;
			float rotate = maths::ConvertToDegrees(maths::GetAngle((click_x - start_posx), (click_y - start_posy)));
			owner_->SetRotation(rotate);



			float x1 = click_x - start_posx;
			float y1 = click_y - start_posy;

		
			math::Vector2D direction;
			math::Vector2DSet(&direction, x1, y1);
			math::Vector2DNormalize(&direction, &direction);


			float bullet_x = start_posx;// +direction.x_ *30.0f;// owner_->get_offset_x() *;
			float bullet_y = start_posy;// +direction.y_*7.0f;// owner_->get_offset_y() * direction.y_;

			owner_->SetPositionX(bullet_x);
			owner_->SetPositionY(bullet_y);

			body_->set_positionX(bullet_x);
			body_->set_positionY(bullet_y);


			float forcex = speed_*direction.x_;
			float forcey = speed_*direction.y_;

			body_->ApplyForceX(forcex);
			body_->ApplyForceY(forcey);

			body_->set_is_physics_on(true);
			owner_->SetActive(true);

			events::EventManager::GetInstance()->SubscribeComponentToEvent(events::E_EVENT_DISABLE_OBJECT, this);
			events::EventManager::GetInstance()->SubscribeComponentToEvent(events::E_EVENT_BULLETHIT, this);

			
			events::Event* disablevent= new events::Event();
			disablevent->set_type(events::E_EVENT_DISABLE_OBJECT);
			disablevent->set_time(time_out_);
			disablevent->set_object_id(get_id());
			events::EventManager::GetInstance()->AddTimedEvent(disablevent);
		}


		void BulletComponent::HandleEvent(events::Event *event) {

			if (is_destroyed_) {

				return;
			}

			if (event->get_type() == events::E_EVENT_DISABLE_OBJECT ) {

				events::Event* disableevent = (event);
				if (disableevent->get_object_id() == get_id() && !is_destroyed_) {
					DestroySelf();
				}
			}
			else if (event->get_type() == events::E_EVENT_BULLETHIT ) {

				//ENGINE_LOG("Bullet Collided");
				events::Event* bulletevent = (event);
				if (bulletevent->get_bullet()->get_id() == owner_->get_id()) {
					
					particlesystem::ParticleManager::GetInstance()->GenerateParticle(body_->get_position().x_, body_->get_position().y_, 2, -10, 10,1.0,1.0,0.0);
  					events::Event healthhit;
					healthhit.set_type(events::E_EVENT_HEALTH_HIT);
					healthhit.set_damage(damage_);
					healthhit.set_other(bulletevent->get_other());
					events::EventManager::GetInstance()->SendEvent(&healthhit);
					DestroySelf();

				}
			}

		}


		void BulletComponent:: DestroySelf() {

			if (is_destroyed_) {

				return;
			}
			events::EventManager::GetInstance()->UnscribeThisComponent(events::E_EVENT_DISABLE_OBJECT, this);
			events::EventManager::GetInstance()->UnscribeThisComponent(events::E_EVENT_BULLETHIT, this);
			owner_->SetPositionX(-100);
			owner_->SetPositionY(-100);
			is_destroyed_ = true;
			body_->ResetBody();
			body_->set_is_physics_on(false);
			owner_->SetActive(false);

		//	ENGINE_LOG("Bullet Destroyed : %d", get_id());
		}
	}
}