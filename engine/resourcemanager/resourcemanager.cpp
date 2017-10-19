#include "resourcemanager.h"

#include "../common/macros.h"
#include "textureloader.h"
#include "../renderer/renderer.h"

#ifdef TEST_MODE
#include "../enginelogger/enginelogger.h"
#endif // TEST_MODE

namespace enginecore {

	namespace resourcemanager {

		ResourceManager* ResourceManager::instance_ = nullptr;

		ResourceManager::ResourceManager() {

			texture_loader_ = new TextureLoader();

		}
		ResourceManager* ResourceManager::GetInstance() {

			if (!ResourceManager::instance_) {

				ResourceManager::instance_ = new ResourceManager();
			}

			return ResourceManager::instance_;
		}

		Sprite* ResourceManager::CreateSprite(std::string path) {

			auto sprite =  texture_loader_->CreateTexture(path);
			renderer::Renderer::GetInstance()->PushToRenderQueue(sprite);

			return sprite;
		}

		void ResourceManager::Destroy() {

			#ifdef TEST_MODE
			ENGINE_LOG("DEstroying the Resource Manager");
			#endif // TEST_MODE

			CLEAN_DELETE(texture_loader_);

			CLEAN_DELETE(ResourceManager::instance_);
		}

		ResourceManager::~ResourceManager() {

		}

	}

}
