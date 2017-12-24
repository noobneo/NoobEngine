

/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: controllercomponent.cpp
Purpose: controller component for the gameobject to be controlled
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 16th October 2017
---------------------------------------------------------*/
#include "controllercomponent.h"
#include "../common/macros.h"
#include "../inputhandler/inputhandler.h"
#include "../inputhandler/keyboardlistener.h"
#include "gameobject.h"
#ifdef TEST_MODE
#include "../enginelogger/enginelogger.h"
#endif
#include "bodycomponent.h"
#include	"../common/scenemanager.h"
#include "rendercomponent.h"
#include "../event/event.h"
#include "../event/eventmanager.h"

namespace enginecore {

	namespace component {

		ControllerComponent::ControllerComponent() {

			owner_ = nullptr;
			body_component_ = nullptr;
			body_component_ = nullptr;
			is_airborne_ = false;
		}


		void ControllerComponent::Update() {


		}


		void ControllerComponent::Init(GameObject* owner) {

			owner_ = owner;
			RegisterKeyBoardListener();
			body_component_ = (BodyComponent*)(owner_->GetComponent(E_COMPONENT_TYPE_BODY));

			events::EventManager::GetInstance()->SubscribeComponentToEvent(events::E_ENABLE_JUMP, this);
		}


		ControllerComponent::~ControllerComponent() {

#ifdef DESTRUCTOR_LOG_MODE
			ENGINE_LOG("DEstroying the ControllerComponent ");
#endif // TEST_MODE
		}




		void ControllerComponent::RegisterKeyBoardListener() {

			auto keyboard_listener = inputhandler::KeyboardListener::CreateListener();

			keyboard_listener->on_key_pressed_ = FUNCTION_CALLBACK(ControllerComponent::OnKeyPressed, this);
			keyboard_listener->on_key_released_ = FUNCTION_CALLBACK(ControllerComponent::OnKeyReleased, this);
		}


		void ControllerComponent::OnKeyPressed(const uint8_t * key_state) {

			if (!active_) {
				return;
			}
			/*serialize these values*/

			if (inputhandler::InputHandler::GetInstance()->IsKeyPressed(SDL_SCANCODE_D)) {

			//	ENGINE_LOG("Right Pressed");
				if (body_component_->get_velocity().x_ <= owner_->get_max_speed())
				body_component_->ApplyForceX(owner_->get_move_force());

				owner_->SetFlipX(1.0f);

			}else if (inputhandler::InputHandler::GetInstance()->IsKeyPressed(SDL_SCANCODE_A)) {


				if (abs(body_component_->get_velocity().x_) <= owner_->get_max_speed()) {

					body_component_->ApplyForceX(-owner_->get_move_force());
				}
				owner_->SetFlipX(-1.0f);
			}

			if (inputhandler::InputHandler::GetInstance()->IsKeyPressed(SDL_SCANCODE_SPACE) || inputhandler::InputHandler::GetInstance()->IsKeyPressed(SDL_SCANCODE_UP)) {


				if (!is_airborne_) {
					is_airborne_ = true;
					body_component_->ApplyForceY(owner_->get_jump_force());

					events::Event *es = new events::Event();
					es->set_object_id(get_id());
					es->set_type(events::E_ENABLE_JUMP);
					es->set_time(.7f);
					events::EventManager::GetInstance()->AddTimedEvent(es);

				}

				//ENGINE_LOG("Up Pressed");


			}

		}

		void ControllerComponent::OnKeyReleased(const uint8_t * key_state) {

			if (!active_) {
				return;
			}

			if (inputhandler::InputHandler::GetInstance()->IsKeyReleased(SDL_SCANCODE_A) || inputhandler::InputHandler::GetInstance()->IsKeyReleased(SDL_SCANCODE_D)) {

				body_component_->set_velocityX(0.0f);

			}

			if (inputhandler::InputHandler::GetInstance()->IsKeyReleased(SDL_SCANCODE_1)) {

				enginecore::EngineConfig::config_->debug_on_ = !enginecore::EngineConfig::config_->debug_on_;

			}

		}



		void ControllerComponent::HandleEvent(events::Event *event) {

			if (event->get_type() == events::E_ENABLE_JUMP && event->get_object_id() == get_id()) {

				if (is_airborne_) {

					is_airborne_ = false;
				}
			}
		}


		void ControllerComponent::Reset() {

			active_ = false;
			owner_ = nullptr;
			body_component_ = nullptr;
			is_airborne_ = false;

			events::EventManager::GetInstance()->UnscribeThisComponent(events::E_ENABLE_JUMP, this);
		}


	}
}
