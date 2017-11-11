#include "physicsmanager.h"

#include "../common/macros.h"
#include "../enginelogger/enginelogger.h"


namespace enginecore {

	namespace physics {

		PhysicsManager* PhysicsManager::instance_ = nullptr;

		PhysicsManager* PhysicsManager::GetInstance() {

			if (!PhysicsManager::instance_) {

				PhysicsManager::instance_ = new PhysicsManager();

			}

			return PhysicsManager::instance_;

		}

		void PhysicsManager::Update() {


		}


		void PhysicsManager::Destroy() {

#ifdef TEST_MODE
			ENGINE_LOG("Destroying the Physics Manager");
#endif // TEST_MODE

		}

	}
}

