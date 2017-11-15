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

namespace enginecore {

	namespace component {

		ControllerComponent::ControllerComponent() {

			body_component_ = nullptr;
			is_airborne_ = false;
		}


		void ControllerComponent::Update() {


		}


		void ControllerComponent::Init(GameObject* owner) {

			owner_ = owner;
			RegisterKeyBoardListener();
			body_component_ = (BodyComponent*)(owner_->GetComponent(E_COMPONENT_TYPE_BODY));
		}


		ControllerComponent::~ControllerComponent() {

#ifdef TEST_MODE
			ENGINE_LOG("DEstroying the ControllerComponent ");
#endif // TEST_MODE
		}


#ifdef TEST_MODE

		void ControllerComponent::RegisterKeyBoardListener() {

			auto keyboard_listener = inputhandler::KeyboardListener::CreateListener();

			keyboard_listener->on_key_pressed_ = FUNCTION_CALLBACK(ControllerComponent::OnKeyPressed, this);
			keyboard_listener->on_key_released_ = FUNCTION_CALLBACK(ControllerComponent::OnKeyReleased, this);
		}


		void ControllerComponent::OnKeyPressed(const Uint8 * key_state) {


			/*serialize these values*/

			if (inputhandler::InputHandler::GetInstance()->IsKeyPressed(SDL_SCANCODE_D)) {

			//	ENGINE_LOG("Right Pressed");
				if (body_component_->get_velocity().x_ <= owner_->get_max_speed())
				body_component_->ApplyForceX(owner_->get_move_force());

			}else if (inputhandler::InputHandler::GetInstance()->IsKeyPressed(SDL_SCANCODE_A)) {


				if (abs(body_component_->get_velocity().x_) <= owner_->get_max_speed()) {

					body_component_->ApplyForceX(-owner_->get_move_force());
				}
				//ENGINE_LOG("Left Pressed");

			}/*else if (key_state[SDL_SCANCODE_DOWN]) {

				ENGINE_LOG("Veclocity :%f", body_component_->get_position().y_);
				body_component_->ApplyForceY(speed);
				//ENGINE[_LOG("Down Pressed");
			}*/


			if (inputhandler::InputHandler::GetInstance()->IsKeyPressed(SDL_SCANCODE_SPACE) || inputhandler::InputHandler::GetInstance()->IsKeyPressed(SDL_SCANCODE_UP)) {


				if (body_component_->get_velocity().y_ >= 0) {

					body_component_->ApplyForceY(-owner_->get_jump_force());
					is_airborne_ = true;
					//body_component_->ApplyForceY(-jump_speed);
				}

				//ENGINE_LOG("Up Pressed");

			}
		}

		void ControllerComponent::OnKeyReleased(const Uint8 * key_state) {

			if (inputhandler::InputHandler::GetInstance()->IsKeyReleased(SDL_SCANCODE_A) || inputhandler::InputHandler::GetInstance()->IsKeyReleased(SDL_SCANCODE_D)) {

				body_component_->set_velocityX(0.0f);
			//	ENGINE_LOG("Right Released");

			}
		/*	else if (key_state[SDL_SCANCODE_A]) {

				body_component_->set_velocityX(0.0f);
			//	ENGINE_LOG("Left Released");

			}
			else if (key_state[SDL_SCANCODE_UP]) {

				//ENGINE_LOG("Up Released");

			}*/
			else if (inputhandler::InputHandler::GetInstance()->IsKeyReleased(SDL_SCANCODE_R)) {

				common::SceneManager::GetInstance()->RestartScene();
			//	ENGINE_LOG("Down Released");
			}
		}
#endif


		void ControllerComponent::Reset() {

			body_component_ = nullptr;
			is_airborne_ = false;
		}


	}
}
