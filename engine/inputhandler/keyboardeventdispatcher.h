#ifndef _KEYBOARD_EVENT_DISPATCHER_H_
#define _KEYBOARD_EVENT_DISPATCHER_H_

/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: keyboardeventdispatcher.h
Purpose: dispatches keyboard events to the listeners
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 17th October 2017
---------------------------------------------------------*/


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
