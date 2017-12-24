
/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: bodyanimationcomponent.cpp
Purpose: animation component for physics body
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 16th October 2017


---------------------------------------------------------*/
#include "bodyanimationcomponent.h"
#include "gameobject.h"
#include "transformcomponent.h"
#include "bodycomponent.h"
#include "../event/eventmanager.h"


#ifdef TEST_MODE
#include "../enginelogger/enginelogger.h"
#endif // TEST_MODE

namespace enginecore {

	namespace component {

		BodyAnimationComponent::BodyAnimationComponent() {

			owner_ = nullptr;
			body_ = nullptr;
			velocity_x_ = 0.0f;
			velocity_y_ = 0.0f;
			direction_ = "y";
			limit_ = 200;
			step_ = 5.0f;
			current_step_ = 0.0;
			dir_ = 1;
		}


		BodyAnimationComponent::~BodyAnimationComponent() {
#ifdef DESTRUCTOR_LOG_MODE
			ENGINE_LOG("Destroying AnimationComponent ");
#endif // TEST_MODE
		}


		void BodyAnimationComponent::Update() {

			if (!active_) {
				return;
			}

			if (current_step_ <= limit_) {

				current_step_ += step_;
				if (direction_ == "y")
					body_->set_velocityY(velocity_y_ *dir_ );
				else
					body_->set_velocityX(velocity_x_ *dir_);
			}
			else {

				current_step_ = 0;
				dir_ *= -1;
			}
		}


		void BodyAnimationComponent::Init(GameObject* owner) {

			owner_ = owner;

			body_ = static_cast<BodyComponent*>(owner_->GetComponent(E_COMPONENT_TYPE_BODY));
			//events::EventManager::GetInstance()->SubscribeComponentToEvent(events::E_EVENT_PLAYERHIT ,this);

		}


		void BodyAnimationComponent::HandleEvent(events::Event *event) {


		}


		void BodyAnimationComponent::Reset() {

			velocity_x_ = 0.0f;
			velocity_y_ = 0.0f;
			active_ = false;
			owner_ = nullptr;
			body_ = nullptr;
			direction_ = "y";
			limit_ = 200;
			step_ = 5.0f;
			current_step_ = 0.0;
			dir_ = 1;
		}

	}
}
