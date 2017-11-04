#include "controllercomponent.h"
#include "../common/macros.h"
#include "../inputhandler/inputhandler.h"
#include "../inputhandler/keyboardlistener.h"
#include "gameobject.h"
#ifdef TEST_MODE
#include "../enginelogger/enginelogger.h"
#endif

namespace enginecore {

	namespace component {

		ControllerComponent::ControllerComponent() {

		}


		void ControllerComponent::Update() {


		}


		void ControllerComponent::Init(GameObject* owner) {

			owner_ = owner;
			RegisterKeyBoardListener();
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


			int speed = 5;
			if (key_state[SDL_SCANCODE_RIGHT]) {

				ENGINE_LOG("Right Pressed");
				owner_->SetPositionX(owner_->get_position_x() + speed);

			}
			else if (key_state[SDL_SCANCODE_LEFT]) {

				owner_->SetPositionX(owner_->get_position_x() - speed);
				ENGINE_LOG("Left Pressed");

			}
			else if (key_state[SDL_SCANCODE_UP]) {

				owner_->SetPositionY(owner_->get_position_y() - speed);
				ENGINE_LOG("Up Pressed");

			}
			else if (key_state[SDL_SCANCODE_DOWN]) {

				owner_->SetPositionY(owner_->get_position_y() + speed);
				ENGINE_LOG("Down Pressed");
			}
		}

		void ControllerComponent::OnKeyReleased(const Uint8 * key_state) {

			if (key_state[SDL_SCANCODE_RIGHT]) {

				ENGINE_LOG("Right Released");

			}
			else if (key_state[SDL_SCANCODE_LEFT]) {

				ENGINE_LOG("Left Released");

			}
			else if (key_state[SDL_SCANCODE_UP]) {

				ENGINE_LOG("Up Released");

			}
			else if (key_state[SDL_SCANCODE_DOWN]) {

				ENGINE_LOG("Down Released");
			}
		}
#endif



	}
}
