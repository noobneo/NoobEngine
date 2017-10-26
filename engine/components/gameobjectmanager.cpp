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

	namespace components {


		GameobjectManager* GameobjectManager::instance_ = nullptr;

		GameobjectManager::GameobjectManager() {

			gameobject_id_		= 0;
			count_				= 0;
			is_clearing_		= false;
			is_deleting_object_ = false;		
		}

		GameobjectManager* GameobjectManager::GetInstance() {

			if (!GameobjectManager::instance_) {

				GameobjectManager::instance_ = new GameobjectManager();
			}

			return GameobjectManager::instance_;
		}


		void GameobjectManager::Update() {

			for (auto &itr : gameobjects_) {

				 itr.second->Update();
			}
		}


		void GameobjectManager::AddGameObject(GameObject* gameobject) {

			int id = gameobject->get_id();
			auto itr = gameobjects_.find(id);

			if (itr == gameobjects_.end()) {

				gameobject->set_id(gameobject_id_);
				gameobjects_[id] = gameobject;
				++count_;
				++gameobject_id_;
				return;
			}

			ENGINE_ERR_LOG("Gameobject with id_ : %d was note found in the queue", itr->second->get_id());
		}


		void GameobjectManager::RemoveObject(int id) {
			
			if (is_clearing_) {

				return;
			} else if (is_deleting_object_) {

				is_deleting_object_ = false;
				return;
			}

			auto itr = gameobjects_.find(id);

			if (itr == gameobjects_.end()) {

				ENGINE_ERR_LOG("Gameobject with id_ : %d was note found in the queue", itr->second->get_id());
				return;
			}
		
			--count_;
			gameobjects_.erase(id);
		}


		void GameobjectManager::DeleteGameobject(int id) {

			auto itr = gameobjects_.find(id);

			if (itr == gameobjects_.end()) {

				ENGINE_ERR_LOG("Gameobject with id_ : %d was note found in the queue", itr->second->get_id());
				return;
			}

			--count_;
			is_deleting_object_ = true;
			delete itr->second;
			gameobjects_.erase(id);
		}


		void GameobjectManager::DeleteAllGameObjects() {

			is_clearing_ = true;
			for (auto &itr : gameobjects_) {

				delete itr.second;
			}

			count_ = 0;
			gameobjects_.clear();
		}

		void GameobjectManager::Destroy() {

	#ifdef TEST_MODE
			ENGINE_LOG("Destroying GameobjectManager");
	#endif // TEST_MODE

			DeleteAllGameObjects();
			CLEAN_DELETE(GameobjectManager::instance_);
		}

	}
}
