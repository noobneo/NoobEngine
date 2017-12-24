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
//#include "componentmanager.h"
#include "gameobject.h"

#include "../common/macros.h"
#include "../enginelogger/enginelogger.h"
#include "../event/event.h"

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

		GameobjectManager* GameobjectManager::GetInstance() {

			if (!GameobjectManager::instance_) {

				GameobjectManager::instance_ = new GameobjectManager();
			}

			return GameobjectManager::instance_;
		}

	
		GameObject* GameobjectManager::CreateGameObject() {

			if (!first_available_) {

				ENGINE_ERR_LOG("No free gamobjects yet!!!");
				return nullptr;
			}

			GameObject *go = first_available_;

			first_available_ = go->get_next();
			active_objects_[go->get_id()] = go;
			return go;
		}

		void GameobjectManager::InitializeGameObject() {
			
			if (!first_available_) {

				ENGINE_ERR_LOG("No free gamobjects yet!!!");
			}

			GameObject *go = first_available_;

			first_available_ = go->get_next();
			active_objects_[go->get_id()] = go;
		}


		GameObject* GameobjectManager::GetGameObjectByTag(std::string name) {

			for (auto &it : active_objects_) {

				if (it.second->get_tag() == name && it.second->get_active()) {

					return it.second;
				}
			}

			return nullptr;
		}

		void GameobjectManager::PoolGameObjects() {

			for (int i = 0; i < MAX_SIZE; ++i) {

				auto gameobject = new GameObject();
				gameobject->set_id(gameobject_id_);
				gameobject->set_next(first_available_);
				first_available_ = gameobject;
				gameobjects_[gameobject_id_] = gameobject;

				++count_;
				++gameobject_id_;
			}
		}


		void GameobjectManager::Update() {

			for (auto &itr : active_objects_) {

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

			for (auto &itr : active_objects_) {
				
				if (itr.second->get_id() == id) {

					itr.second->set_next(first_available_->get_next());
					first_available_ = itr.second;
					active_objects_.erase(id);
					return;
				}
			}
		}


		void GameobjectManager::ClearPool() {

			for (auto itr : gameobjects_) {

				delete itr;
			}
			count_ = 0;
			gameobject_id_ = 0;
			active_objects_.clear();
//			gameobjects_.clear();
		}


		void GameobjectManager::Reset() {
			
			for (auto &itr : active_objects_) {

				itr.second->set_next(first_available_);
				first_available_ = itr.second;
				itr.second->Reset();
			}

			active_objects_.clear();
		}


		void GameobjectManager::BroadCastEvent(events::Event* event) {

			for (auto &itr : active_objects_) {

				itr.second->HandleEvent(event);
			}
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
