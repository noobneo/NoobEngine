#include "serializer.h"

#ifdef TEST_MODE
#include "../enginelogger/enginelogger.h"
#endif // TEST_MODE
#include "../common/macros.h"
#include "../components/gameobjectmanager.h"

namespace enginecore {

	namespace serialize {
		
		Serializer* Serializer::instance_ = nullptr;

		Serializer* Serializer::GetInstance() {

			if (!instance_) {

				instance_ = new Serializer();
			}

			return instance_;
		}

		void Serializer::SerializeGameData(std::string filename) {

			auto obj = component::GameobjectManager::GetInstance()->CreateGameObject();
			

		}

		void Serializer::Destroy() {

#ifdef TEST_MODE
			ENGINE_LOG("Destroying Serializer");
#endif // TEST_MODE

			CLEAN_DELETE(instance_);
		}
	}

}

