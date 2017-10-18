#ifndef _KEYBOARD_EVENT_DISPATCHER_H_
#define _KEYBOARD_EVENT_DISPATCHER_H_

#include "../common/macros.h"

namespace enginecore {

	namespace inputhandler {


		class KeyboardListener {
		 
		public :

			KeyboardListener()=default;
			~KeyboardListener() = default;

		private:


			std::function<void()> on_pressed_;
			void* on_released_;

		};

		class KeyboardEventDispatcher
		{
		public:


			static KeyboardEventDispatcher* GetInstance();

			

		private:
			KeyboardEventDispatcher()=default;
			~KeyboardEventDispatcher() = default;

			KeyboardEventDispatcher(const KeyboardEventDispatcher&) = delete;
			KeyboardEventDispatcher& operator=(const KeyboardEventDispatcher&) = delete;

		private:

			static KeyboardEventDispatcher* isntance_;
		};

	}
}


#endif // !_EVENT_DISPATCHER_H_
