#include "gameobjectmanager.h"
#include "../common/macros.h"


#ifdef TEST_MODE
#include "../enginelogger/enginelogger.h"
#endif // TEST_MODE


namespace enginecore {

	namespace components {


	GameobjectManager* GameobjectManager::instance_ = nullptr;

	GameobjectManager::GameobjectManager() {

		gameobject_id_ = -1;
	}

	GameobjectManager* GameobjectManager::GetInstance() {

		if (!GameobjectManager::instance_) {

			GameobjectManager::instance_ = new GameobjectManager();
		}

		return GameobjectManager::instance_;
	}

	void GameobjectManager::Destroy() {

#ifdef TEST_MODE
		ENGINE_LOG("Destroying GameobjectManager");
#endif // TEST_MODE

		CLEAN_DELETE(GameobjectManager::instance_);
	}

	GameobjectManager::~GameobjectManager() {

	}

	}
}
