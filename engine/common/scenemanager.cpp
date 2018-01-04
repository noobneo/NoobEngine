
/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: scenemanager.h
Purpose: manages changing of scenes
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 14th October 2017
---------------------------------------------------------*/



#include "scenemanager.h"
#include "../components/gameobjectmanager.h"
#include "../engine.h"
#include "../physics/physicsmanager.h"
#include "../components/componentmanager.h"
#include "../components/objectfactory.h"
#include "../inputhandler/inputhandler.h"
#include "../event/eventmanager.h"
#include "../graphics/renderer.h"
#include "../common/macros.h"
#include "../particlemanager/particlemanager.h"

#include "../enginelogger/enginelogger.h"
#include "../serializer/serializer.h"


namespace enginecore {

	namespace common {

		SceneManager* SceneManager::instance_ = nullptr;

		SceneManager* SceneManager::GetInstance() {

			if (!SceneManager::instance_) {

				SceneManager::instance_ = new SceneManager();
			}

			return SceneManager::instance_;
		}


		void SceneManager::Destroy() {

#ifdef TEST_MODE
			ENGINE_LOG("DEstroying the SceneManager");
#endif // TEST_MODE


			CLEAN_DELETE(SceneManager::instance_);
		}


	/*	void SceneManager::RestartScene() {

			enginecore::Engine::GetInstance()->set_is_scene_change(true);
		}*/

		void SceneManager::ResetAndSerializeScene() {

			//physics
			physics::PhysicsManager::GetInstance()->Reset();
			//render
			graphics::Renderer::GetInstance()->Reset();
			//components
			component::ComponentManager::GetInstance()->Reset();
			//gameobjects
			component::GameobjectManager::GetInstance()->Reset();
			//inputhandler
			inputhandler::InputHandler::GetInstance()->Reset();
			//eventsmanager
			events::EventManager::GetInstance()->Reset();

			//partic;es
			particlesystem::ParticleManager::GetInstance()->Reset();

			//component::ObjectFactory::GetInstance()->ReloadLevel();

			if (!scene_path_.size()) {

				scene_path_ = "gamelevel1";
			}
			std::string path = "playground/resources/gamedata/scenes/" + scene_path_ + ".json";
			enginecore::serialize::Serializer::GetInstance()->SerializeGameData(path);
			enginecore::Engine::GetInstance()->set_is_scene_change(false);
		}

		void SceneManager::LoadScene(std::string path) {


			previous_scene_path_ = scene_path_;
			scene_path_ = path;
			enginecore::Engine::GetInstance()->set_is_scene_change(true);
		}

		void SceneManager::LoadLastLevel() {

			LoadScene(previous_scene_path_);
		}

		int SceneManager::GetLevelNoFromFileName(std::string name) {


			int no=1;
			if (name == "gamelevel1") {

				no =  1;
			}else if (name == "gamelevel2") {

				no = 2;
			}
			else if (name == "bosslevel") {

				no = 3;
			}

			return no;
		}

		void SceneManager::NextLevel() {

			++levelno_;
			levelno_ = levelno_ > enginecore::EngineConfig::config_->max_level_ ? 1 : levelno_;


			std::string levelname("level");

			switch (levelno_) {
				
			case 1:
				levelname += "1";
				break;

			case 2:
				levelname += "2";
				break;

			case 3:
				levelname += "3";
				break;
			}

			levelname += "menu";

			LoadScene(levelname);
		}


	}
}