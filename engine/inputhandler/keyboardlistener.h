
#ifndef _KEYBOARD_EVENT_LISTENER_H_
#define _KEYBOARD_EVENT_LISTENER_H_


/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: keyboardlistener.h
Purpose: listener for the keyboard events
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 18th October 2017
---------------------------------------------------------*/


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
