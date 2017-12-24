

/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: healthcomponent.cpp
Purpose: adds health attribute to the gameobject
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 16th October 2017
---------------------------------------------------------*/



#include "healthcomponent.h"

#ifdef  DEBUG_MODE
#include "../enginelogger/enginelogger.h"

#endif //  DEBUG_MODE

#include "../enginelogger/enginelogger.h"
#include "../event/event.h"
#include "../event/eventmanager.h"
#include "rendercomponent.h"


namespace enginecore {

	namespace component {

		void HealthComponent::Update() {

		}

		void HealthComponent::Init(GameObject* owner) {

			owner_ = owner;
			events::EventManager::GetInstance()->SubscribeComponentToEvent(events::E_EVENT_HEALTH_HIT, this);
		}


		HealthComponent::HealthComponent() {

			
		}
		HealthComponent::~HealthComponent() {

			Reset();

		}
			
		void HealthComponent::Reset() {


			owner_ = nullptr;
			events::EventManager::GetInstance()->UnscribeThisComponent(events::E_EVENT_HEALTH_HIT, this);
		}
		
		void HealthComponent::HandleEvent(events::Event *event) {

			if (event->get_type() == events::E_EVENT_HEALTH_HIT && event->get_other()->get_id() == owner_->get_id()) {

				health_ -= event->get_damage();

				RenderComponent* render = static_cast<RenderComponent*> (owner_->GetComponent(E_COMPONENT_TYPE_RENDER));
				render->SetBlink(true);

				if (health_ <= 0) {

					events::EventManager::GetInstance()->UnscribeThisComponent(events::E_EVENT_HEALTH_HIT, this);
					owner_->Die();
				}

				if (owner_->get_tag() == "player") {

					events::Event ev;
					ev.set_type(events::E_PLAYER_DEATH);
					events::EventManager::GetInstance()->SendEvent(&ev);
				}
			
  				if (owner_->get_tag() == "boss") {

					events::Event ev;
					ev.set_type(events::E_BOSS_DEATH);
					events::EventManager::GetInstance()->SendEvent(&ev);
				}
#ifdef  DEBUG_MODE
				ENGINE_LOG("hit current health after damage : %d ", health_)
#else 
				ENGINE_ERR_LOG("hit current health after damage : %d ", health_);
#endif //  DEBUG_MODE
			}

		}

	}
}
