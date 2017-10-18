#ifndef _KEYBOARD_EVENT_DISPATCHER_H_
#define _KEYBOARD_EVENT_DISPATCHER_H_

#include <unordered_map>
#include "keyboardlistener.h"

namespace enginecore {

	namespace inputhandler {


		class KeyboardEventListener;

		class KeyboardEventDispatcher
		{
		public:

			static KeyboardEventDispatcher* GetInstance();


			void Destroy();

			void OnKeyPressed(const Uint8*);
			void OnKeyReleased(const Uint8*);
			
			int Register(KeyboardListener* listener);


			inline int get_total_listeners() { return total_listeners_; };

		private:
			KeyboardEventDispatcher();
			~KeyboardEventDispatcher()=default;

			void UnRegisterListeners();
			KeyboardEventDispatcher(const KeyboardEventDispatcher&) = delete;
			KeyboardEventDispatcher& operator=(const KeyboardEventDispatcher&) = delete;

		private:

			static KeyboardEventDispatcher* instance_;
			std::unordered_map<int, KeyboardListener*> listeners_;
			int total_listeners_;
		};

	}
}


#endif // !_EVENT_DISPATCHER_H_
