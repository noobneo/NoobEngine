/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: gameobject.h
Purpose: its a game object class
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 25th October 2017
---------------------------------------------------------*/

#include "gameobject.h"
#include "gameobjectmanager.h"
#include "../enginelogger/enginelogger.h"

namespace enginecore {

	namespace component {

		GameObject::GameObject() {

			id_			= -1;
			next_		= nullptr;
			is_active_	= false;
		}

		void GameObject::Update(){

		}

		GameObject::~GameObject() {


#ifdef TEST_MODE
		//	ENGINE_LOG("Destroying Gameobject :%d",id_);
#endif // TEST_MODE
			components_.clear();
			id_ = -1;
			next_ = nullptr;
			is_active_ = false;
		}
	}
}
