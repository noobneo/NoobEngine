
#ifndef _MOUSE_EVENT_LISTENER_H_
#define _MOUSE_EVENT_LISTENER_H_


/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: mouselistener.h
Purpose: listener for the mouse events
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 28th November 2017
---------------------------------------------------------*/


#include "../common/macros.h"



namespace enginecore {

	namespace inputhandler {

		class MouseEventListener {

		public:

			static MouseEventListener* CreateListener();
			

			~MouseEventListener();
		private:
			MouseEventListener();

			int id_;
			
		public:

			std::function<void (uint32_t ,int ,int) > mouse_event_;
		};
	}

}

#endif // !_KEYBOARD_EVENT_LISTENER_H_
