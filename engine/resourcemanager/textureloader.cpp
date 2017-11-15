#include "textureloader.h"
#include "../enginelogger/enginelogger.h"

namespace enginecore {

	namespace resourcemanager {


		TextureLoader::TextureLoader(){

		}

		graphics::Sprite* TextureLoader::CreateTexture(std::string path) {

			auto itr = textures_.find(path);
			SDL_Surface* surface = nullptr;

			if (itr != textures_.end()) {

				surface =  itr->second;
			}
			else {

				surface = SDL_LoadBMP(path.c_str());

				if (!surface) {

					ENGINE_ERR_LOG("Error creating Bmp :%s", path.c_str());
				}

				textures_[path] = surface;
			}


			graphics::Sprite* sprite = new graphics::Sprite();
			sprite->set_surface(surface);
			/*sprite*/

			return  sprite;
		}


		TextureLoader::~TextureLoader(){
			
			for (auto &itr : textures_) {

				SDL_FreeSurface(itr.second);
				#ifdef TEST_MODE
					ENGINE_LOG("DEstroying the SDL_Surface");
				#endif // TEST_MODE
			}

			textures_.clear();

			#ifdef TEST_MODE
				ENGINE_LOG("DEstroying the TextureLoader Manager");
			#endif // TEST_MODE

		}


	}
}
