
/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: keyboardlistener.cpp
Purpose: listener for the keyboard events
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 18th October 2017
---------------------------------------------------------*/


#include "keyboardlistener.h"
#include "keyboardeventdispatcher.h"


#ifdef TEST_MODE
	#include "../enginelogger/enginelogger.h"
#endif // TEST_MODE

namespace enginecore {

	namespace inputhandler {

		KeyboardListener::KeyboardListener() {

			id_ = KeyboardEventDispatcher::GetInstance()->Register(this);

#ifdef TEST_MODE
			ENGINE_LOG("Creating KeyboardListener :%d", id_);
#endif // TEST_MODE
		}

		KeyboardListener* KeyboardListener::CreateListener() {

			KeyboardListener* listener = new KeyboardListener();
			return listener;
		}

		KeyboardListener::~KeyboardListener() {
#ifdef TEST_MODE
			ENGINE_LOG("Deleting KeyboardListener :%d",id_);
#endif // TEST_MODE
		}
	}
}

