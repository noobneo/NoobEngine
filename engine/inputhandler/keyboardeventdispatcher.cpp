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


		KeyboardEventDispatcher::KeyboardEventDispatcher(){

			total_listeners_ = 0;
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
