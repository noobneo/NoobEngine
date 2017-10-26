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

	namespace components {

		GameObject::GameObject() {

			GameobjectManager::GetInstance()->AddGameObject(this);
		}

		GameObject* GameObject::Create() {

			GameObject* obj = nullptr;
			obj = new GameObject();
			if (obj) {

				ENGINE_ERR_LOG("Could not create game object");
				return nullptr;
			}
			return obj;
		}

		void GameObject::Update(){

		}

		GameObject::~GameObject() {

			GameobjectManager::GetInstance()->RemoveObject(id_);
			id_ = -1;
		}


	}
}
