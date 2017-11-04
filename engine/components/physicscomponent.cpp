#include "physicscomponent.h"

#ifdef  TEST_MODE
#include "../enginelogger/enginelogger.h"
#endif //  TEST_MODE


namespace enginecore {

	namespace component {

		PhysicsComponent::PhysicsComponent() {

		}


		void PhysicsComponent::Init(GameObject* owner) {

			owner_ = owner;
		}

		void PhysicsComponent::Update() {

#ifdef  TEST_MODE
			ENGINE_LOG("Hey updating the physics");
#endif //  TEST_MODE

		}

		PhysicsComponent::~PhysicsComponent() {

#ifdef TEST_MODE
			ENGINE_LOG("Destroying Physics Component");
#endif // TEST_MODE

		}

	}

}

