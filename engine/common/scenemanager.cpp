#include "scenemanager.h"
#include "../components/gameobjectmanager.h"
#include "../engine.h"
#include "../physics/physicsmanager.h"
#include "../components/componentmanager.h"
#include "../components/objectfactory.h"
#include "../inputhandler/inputhandler.h"
#include "../renderer/renderer.h"
#include "../common/macros.h"
#ifdef TEST_MODE
#include "../enginelogger/enginelogger.h"
#endif // TEST_MODE


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


		void SceneManager::RestartScene() {

			enginecore::Engine::GetInstance()->set_is_scene_restart(true);
		}

		void SceneManager::ResetManagers() {

			//physics
			physics::PhysicsManager::GetInstance()->Reset();
			//render
			renderer::Renderer::GetInstance()->Reset();
			//components
			component::ComponentManager::GetInstance()->Reset();
			//gameobjects
			component::GameobjectManager::GetInstance()->Reset();
			//inputhandler
			inputhandler::InputHandler::GetInstance()->Reset();

			component::ObjectFactory::GetInstance()->ReloadLevel();
			enginecore::Engine::GetInstance()->set_is_scene_restart(false);
		}
	
	}
}