
#ifndef _KEYBOARD_EVENT_LISTENER_H_
#define _KEYBOARD_EVENT_LISTENER_H_

#include "../common/macros.h"
#include "../../external/SDL2.0 Lib/include/SDL.h"
	
namespace enginecore {

	namespace inputhandler {

		class KeyboardListener {

		public:

			static KeyboardListener* CreateListener();

			~KeyboardListener();
		private:
			KeyboardListener() ;

			int id_;

		public:
			

			std::function<void(const Uint8*)> on_key_pressed_;
			std::function<void(const Uint8*)> on_key_released_;
		};
	}

}

#endif // !_KEYBOARD_EVENT_LISTENER_H_
