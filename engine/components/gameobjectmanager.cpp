/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: gameobjectmanager.cpp
Purpose: game object manager which is a singleton class which helps in managing the gameobjects
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 25th October 2017
---------------------------------------------------------*/

#include "gameobjectmanager.h"
#include "../common/macros.h"
#include "../enginelogger/enginelogger.h"
#include "gameobject.h"

namespace enginecore {

	namespace component {

		GameobjectManager* GameobjectManager::instance_ = nullptr;

		GameobjectManager::GameobjectManager() {

			gameobject_id_		= 0;
			count_				= 0;
			first_available_	= nullptr;

			PoolGameObjects();

#ifdef TEST_MODE
			IteratePool();
#endif // TEST_MODE
		}

		void GameobjectManager::PoolGameObjects() {

			for (int i = 0; i < MAX_SIZE; ++i) {

				++count_;
				++gameobject_id_;
				auto gameobject = new GameObject();
				gameobject->set_id(gameobject_id_);
				gameobject->set_next(first_available_);
				first_available_ = gameobject;
				gameobjects_[gameobject_id_] = gameobject;
			}
		}


		GameobjectManager* GameobjectManager::GetInstance() {

			if (!GameobjectManager::instance_) {

				GameobjectManager::instance_ = new GameobjectManager();
			}

			return GameobjectManager::instance_;
		}

		GameObject* GameobjectManager::CreateGameObject() {

			return nullptr;
		}

		void GameobjectManager::Update() {

			for (auto &itr : gameobjects_) {

				 itr.second->Update();
			}
		}


#ifdef TEST_MODE

		void GameobjectManager::IteratePool() {

			GameObject *temp = first_available_;

			while (temp) {
				ENGINE_LOG("Gameobject with id : %d",temp->get_id());
				temp = temp->get_next();
			}
		}
#endif // TEST_MODE


		void GameobjectManager::DeleteGameobject(int id) {


		}


		void GameobjectManager::ClearPool() {

			for (auto &itr : gameobjects_) {

				delete itr.second;
			}
			count_ = 0;
			gameobject_id_ = 0;
			gameobjects_.clear();
		}

		void GameobjectManager::Destroy() {

	#ifdef TEST_MODE
			ENGINE_LOG("Destroying GameobjectManager");
	#endif // TEST_MODE

			ClearPool();
			CLEAN_DELETE(GameobjectManager::instance_);
		}

	}
}
