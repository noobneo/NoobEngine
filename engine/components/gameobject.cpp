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

		void GameObject::AttachComponent(MainComponent * component, ComponentType type) {

			auto itr = components_.find(type);

			if (itr != components_.end()) {

				ENGINE_ERR_LOG("Component already attached ! Make sure you remove it first to add different");
				return;
			}
			components_[type] = component;
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
