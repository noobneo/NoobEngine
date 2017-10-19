/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: inputhandler.cpp
Purpose: manages keyboard input and delegates the events to keyboardeventdispatcher
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 17th October 2017
---------------------------------------------------------*/


#include "inputhandler.h"
#include <string.h>

#ifdef TEST_MODE
	#include "../common/macros.h"
	#include "../enginelogger/enginelogger.h"
#endif // TEST_MODE

#include "../engine.h"

#include "keyboardeventdispatcher.h"

namespace enginecore{

	namespace inputhandler {

		InputHandler* InputHandler::instance_ = nullptr;

		InputHandler::InputHandler() {


			memset(previous_key_board_state_, 0, sizeof(Uint8)*MAX_KEYS);
			pump_state_ = SDL_GetKeyboardState(NULL);
			memcpy(current_key_board_state_, pump_state_, sizeof(Uint8)*MAX_KEYS);
			memcpy(previous_key_board_state_, current_key_board_state_, sizeof(Uint8)*MAX_KEYS);
		}

		InputHandler* InputHandler::GetInstance() {

			if (!InputHandler::instance_) {

				InputHandler::instance_ = new InputHandler();
			}

			return InputHandler::instance_;
		}

		bool InputHandler::IsKeyPressed(KEY_CODE key) {

			
			
			if (current_key_board_state_[key]) {

				#ifdef TEST_MODE
					ENGINE_LOG("Key Pressed");
				#endif // TEST_MODE

			}

			return ((current_key_board_state_[key]) == 1);
		}

		bool InputHandler::IsKeyReleased(KEY_CODE key) {


			#ifdef TEST_MODE
				if (((current_key_board_state_[key]) == 0 && (previous_key_board_state_[key]) == 1)) {

					ENGINE_LOG("Key Released %d", (current_key_board_state_[key]) ^ (previous_key_board_state_[key]));
				}
			#endif // TEST_MODE

			return ((current_key_board_state_[key])==0 && (previous_key_board_state_[key]) == 1);
		}

		bool InputHandler::IsKeyTriggered(KEY_CODE key) {

			#ifdef TEST_MODE
				if (((current_key_board_state_[key]) == 1 && (previous_key_board_state_[key]) == 0)) {

					ENGINE_LOG("Key Triggered %d", (current_key_board_state_[key]) ^ (previous_key_board_state_[key]));
				}
			#endif // TEST_MODE

				return ((current_key_board_state_[key]) == 1 && (previous_key_board_state_[key]) == 0);
		}

		void InputHandler::Destroy() {

			#ifdef TEST_MODE
				ENGINE_LOG("Destroying InputHandler");
			#endif // TEST_MODE

			KeyboardEventDispatcher::GetInstance()->Destroy();
			CLEAN_DELETE(InputHandler::instance_);
		}

		bool InputHandler::Update() {

			memcpy(previous_key_board_state_, current_key_board_state_, sizeof(Uint8)*MAX_KEYS);
			memcpy(current_key_board_state_,pump_state_, sizeof(Uint8)*MAX_KEYS);
			//SDL_PumpEvents();
			

			if (SDL_PollEvent(&event_) != 0) {

				if (event_.type == SDL_QUIT){
					#ifdef TEST_MODE
						ENGINE_LOG("Quit Event Called");
					#endif // TEST_MODE
					return false;
				}
				else {

					if (event_.type == SDL_KEYDOWN) {

						DelegateKeyPressed();

					}else if (event_.type == SDL_KEYUP) {

						DelegateKeyReleased();
					}
				}
			}

			return true;
		}


		void InputHandler::DelegateKeyReleased() {

			KeyboardEventDispatcher::GetInstance()->OnKeyReleased(previous_key_board_state_);
		}

		void InputHandler::DelegateKeyPressed() {

			KeyboardEventDispatcher::GetInstance()->OnKeyPressed(current_key_board_state_);
		}


		InputHandler::~InputHandler() {

		}
	}

}
