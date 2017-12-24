
/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: buttoncomponent.cpp
Purpose: button behaviour component
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 16th October 2017


---------------------------------------------------------*/
#include "buttoncomponent.h"
#include "../inputhandler/mouselistener.h"
#include "../inputhandler/mouseeventdispatcher.h"
#include "../common/macros.h"
#include "../enginelogger/enginelogger.h"
#include "../common/scenemanager.h"
#include "gameobject.h"
#include "transformcomponent.h"
#include "rendercomponent.h"
#include "../maths/vector2D.h"
#include "../event/eventmanager.h"
#include "../event/event.h"


namespace enginecore {

	namespace component {

		ButtonComponent::ButtonComponent() {

			button_down_ = false;
			button_up_ = false;
			owner_ = nullptr;
		

			 max_x=0.0f;
			 max_y=0.0f;
			 min_x=0.0f;
			 min_y =0.0f;
				 
		}

		void ButtonComponent::Update() {


		}


		void ButtonComponent::Init(GameObject* owner) {

			owner_ = owner;
			RegisterForMouseEvent();
			events::EventManager::GetInstance()->SubscribeComponentToEvent(events::E_BUTTON_CLICK_EVENT, this);
		}
		ButtonComponent::~ButtonComponent() {

		}

		void ButtonComponent::RegisterForMouseEvent() {

				auto listener = inputhandler::MouseEventListener::CreateListener();
				listener->mouse_event_ = FUNCTION_CALLBACK2(ButtonComponent::MouseEvent, this);
		}

		void ButtonComponent::MouseEvent(uint32_t type, int x, int y) {


			switch (type) {

				case SDL_MOUSEMOTION:
				{	
					break;
				}
				case SDL_MOUSEBUTTONDOWN:
				{
					if (!button_down_) {
						if (CheckIfInBounds(x, y)) {

							button_down_ = true;
							owner_->SetScaleX(1.1f);
							owner_->SetScaleY(1.1f);
							ENGINE_LOG("button pressed");
						}
					}
					break;
				}

				case SDL_MOUSEBUTTONUP:
				{
					if (button_down_) {
						button_down_ = false;
						if(CheckIfInBounds(x, y) ){

							events::Event *ev = new events::Event();
							ev->set_type(events::E_BUTTON_CLICK_EVENT);
							ev->set_time(.1f);
							ev->set_object_id(get_id());
							events::EventManager::GetInstance()->AddTimedEvent(ev);
							//ButtonPressed();
						}
						owner_->SetScaleX(1.0f);
						owner_->SetScaleY(1.0f);
						ENGINE_LOG("button lifted");
					}
					break;
				}
			}


		}

		bool ButtonComponent::CheckIfInBounds(int x , int y) {

			if (x<min_x || x>max_x || y > max_y || y < min_y) {

				return false;
			}

			return true;
		}


		void ButtonComponent::ButtonPressed() {


			if (owner_->get_tag() == "retrybtn") {

				events::Event rs;// = new events::Event();
				rs.set_type(events::E_RESTART);
			//	rs->set_time(.1f);
				events::EventManager::GetInstance()->SendEvent(&rs);
			}
			else {

				common::SceneManager::GetInstance()->LoadScene(file_to_open_);
			}
		}


		void ButtonComponent::Reset() {
	
			button_down_ = false;
			button_up_ = false;
			owner_ = nullptr;
			

			max_x = 0.0f;
			max_y = 0.0f;
			min_x = 0.0f;
			min_y = 0.0f;

		}


		void ButtonComponent::HandleEvent(events::Event *event) {

			if (event->get_type() == events::E_BUTTON_CLICK_EVENT && event->get_object_id()== get_id()) {

				events::EventManager::GetInstance()->UnscribeThisComponent(events::E_BUTTON_CLICK_EVENT, this);
				ButtonPressed();
			}

		}

		void ButtonComponent::UpdateProperties() {


			TransformComponent* transform = static_cast<TransformComponent*>( owner_->GetComponent(E_COMPONENT_TYPE_TRANSFORM));
			RenderComponent* render = static_cast<RenderComponent*>(owner_->GetComponent(E_COMPONENT_TYPE_RENDER));

			max_x = render->get_width()*.5f + transform->get_position_x();
			max_y = render->get_height()*.5f + transform->get_position_y();


			min_x = transform->get_position_x() - render->get_width()*.5f  ;
			min_y = transform->get_position_y() - render->get_height()*.5f  ;


		}

	}
}
