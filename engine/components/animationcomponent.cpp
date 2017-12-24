
/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: animationcomponent.xpp
Purpose: animation component
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 16th October 2017
---------------------------------------------------------*/


#include "animationcomponent.h"
#include "gameobject.h"
#include "transformcomponent.h"
#include "../event/eventmanager.h"


#ifdef TEST_MODE
	#include "../enginelogger/enginelogger.h"
#endif // TEST_MODE

namespace enginecore {

	namespace component {

		AnimationComponent::AnimationComponent() {

			owner_ = nullptr;
			transform_ = nullptr;
			direction_ = "y";
			limit_ = 200;
			step_ = 5.0f;
			current_step_ = 0.0;
			dir_ = 1;
		}


		AnimationComponent::~AnimationComponent() {
#ifdef DESTRUCTOR_LOG_MODE
			ENGINE_LOG("Destroying AnimationComponent ");
#endif // TEST_MODE
		}


		void AnimationComponent::Update() {


			if (!active_) {
				return;
			}
		
			if (current_step_ <= limit_) {

				current_step_ += step_;
				if(direction_ == "y")
					transform_->SetPositionY(transform_->get_position_y() + step_*dir_);
				else 
					transform_->SetPositionX(transform_->get_position_x() + step_*dir_);
			}
			else {

				current_step_ = 0;
				dir_ *= -1;
			}
		}


		void AnimationComponent::Init(GameObject* owner) {

			owner_ = owner;
			transform_ = static_cast<TransformComponent*>( owner_->GetComponent(E_COMPONENT_TYPE_TRANSFORM));

			//events::EventManager::GetInstance()->SubscribeComponentToEvent(events::E_EVENT_PLAYERHIT ,this);

		}


		void AnimationComponent::HandleEvent(events::Event *event) {


		/*	if (event->get_type() == events::E_EVENT_PLAYERHIT) {

			//	ENGINE_LOG("Subscribed to PlayerHit - Reversing My Direction");
				TransformComponent* transform_comp = static_cast<TransformComponent*>(owner_->GetComponent(E_COMPONENT_TYPE_TRANSFORM));
				transform_comp->SetPositionX(400);

			}*/

		}


		void AnimationComponent::Reset() {

			active_ = false;
			transform_ = nullptr;
			owner_ = nullptr;
			direction_ = "y";
			limit_ = 200;
			step_ = 5.0f;
			current_step_ = 0.0;
			dir_ = 1;
		}

	}
}
