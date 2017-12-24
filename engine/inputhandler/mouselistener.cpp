


/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: mouselistener.cpp
Purpose: listener for the mouse events
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 28th November 2017
---------------------------------------------------------*/



#include "mouselistener.h"
#include "mouseeventdispatcher.h"


#ifdef TEST_MODE
#include "../enginelogger/enginelogger.h"
#endif // TEST_MODE

namespace enginecore {

	namespace inputhandler {

		MouseEventListener::MouseEventListener() {

			id_ = MouseEventDispatcher::GetInstance()->Register(this);

#ifdef TEST_MODE
			ENGINE_LOG("Creating MouseEventListener :%d", id_);
#endif // TEST_MODE
		}

		
		MouseEventListener* MouseEventListener::CreateListener() {

			MouseEventListener* listener = new MouseEventListener();
			return listener;
		}


		MouseEventListener::~MouseEventListener() {
#ifdef TEST_MODE
			ENGINE_LOG("Deleting MouseEventListener :%d", id_);
#endif // TEST_MODE
		}
	}
}

