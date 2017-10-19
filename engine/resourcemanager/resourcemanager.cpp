#include "resourcemanager.h"

#include "../common/macros.h"
#ifdef TEST_MODE
#include "../enginelogger/enginelogger.h"
#endif // TEST_MODE

namespace enginecore {

	namespace resourcemanager {

		ResourceManager* ResourceManager::instance_ = nullptr;

		ResourceManager* ResourceManager::GetInstance() {

			if (!ResourceManager::instance_) {

				ResourceManager::instance_ = new ResourceManager();
			}

			return ResourceManager::instance_;
		}

		SDL_Surface* ResourceManager::CreateSprite(std::string path) {

			auto itr = textures_.find(path);

			if (itr != textures_.end()) {

				return itr->second;
			}

			SDL_Surface* surface = SDL_LoadBMP(path.c_str());

			if (!surface) {

				ENGINE_ERR_LOG("Error creating Bmp :%s", path.c_str());
			}

			textures_[path] = surface;

			return surface;
		}

		void ResourceManager::Destroy() {

			for (auto &itr : textures_) {

				SDL_FreeSurface(itr.second);
			}

			textures_.clear();

			#ifdef TEST_MODE
			ENGINE_LOG("DEstroying the Resource Manager");
			#endif // TEST_MODE


			CLEAN_DELETE(ResourceManager::instance_);
		}

	}

}
