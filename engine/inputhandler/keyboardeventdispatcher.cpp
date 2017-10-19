/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: keyboardeventdispatcher.cpp
Purpose: dispatches keyboard events to the listeners
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 17th October 2017
---------------------------------------------------------*/



#include "keyboardeventdispatcher.h"
#include "../enginelogger/enginelogger.h"
#include "../common/macros.h"


namespace enginecore {


	namespace inputhandler {

		KeyboardEventDispatcher* KeyboardEventDispatcher::instance_ = nullptr;

		KeyboardEventDispatcher* KeyboardEventDispatcher::GetInstance() {

			if (!KeyboardEventDispatcher::instance_) {

				KeyboardEventDispatcher::instance_ = new KeyboardEventDispatcher();
			}

			return KeyboardEventDispatcher::instance_;
		}

		void KeyboardEventDispatcher::OnKeyPressed(const Uint8* key_states) {

			for (auto &it : listeners_) {

				try {
					it.second->on_key_pressed_(key_states);
				}
				catch (const std::bad_function_call& e) {
					ENGINE_ERR_LOG("Bad Function Call :%s", e.what());
				}
			}
		}


		void KeyboardEventDispatcher::OnKeyReleased(const Uint8* key_states) {

			for (auto &it : listeners_) {

				try {
					it.second->on_key_released_(key_states);
				}
				catch (const std::bad_function_call& e) {
					ENGINE_ERR_LOG("Bad Function Call :%s", e.what());
				}
			}
		}


		int KeyboardEventDispatcher::Register(KeyboardListener* listener) {
			
			if (!listener) {

				return -1;
			}

			++total_listeners_;
			listeners_[total_listeners_] = listener;
			return total_listeners_;
		}


		void KeyboardEventDispatcher::UnRegisterListeners() {

			for (auto &it : listeners_) {

				auto listener = it.second;
				--total_listeners_;
				CLEAN_DELETE(listener);
			}
			listeners_.clear();

		}

		void KeyboardEventDispatcher::Destroy() {

#ifdef TEST_MODE
			ENGINE_LOG("Destroying KeyboardEventDispatcher");
#endif // TEST_MODE

			UnRegisterListeners();
			CLEAN_DELETE(KeyboardEventDispatcher::instance_);
		}

	}
}
