#include "textureloader.h"
#include "../enginelogger/enginelogger.h"
#include "../../external/stb/stb_image.h"

namespace enginecore {

	namespace resourcemanager {


		TextureLoader::TextureLoader(){

		}

		graphics::Sprite* TextureLoader::CreateTexture(std::string path) {
			
		
#ifdef USE_SDL

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


		
			sprite->set_surface(surface);
			/*sprite*/
#else
		int width=0, height=0, nrChannels;
		unsigned char *data;
		graphics::Sprite* sprite = nullptr;

		auto itr = textures_.find(path);

		if (itr != textures_.end()) {

			data = itr->second->data_;
			width = itr->second->width_;
			height = itr->second->height_;
			nrChannels = itr->second->nrChannels_;

			sprite = new graphics::Sprite(data, width, height , nrChannels);
			sprite->set_name(path);
		}
		else {

			Texture * texture = nullptr;
			stbi_set_flip_vertically_on_load(true);
			data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
			if (data)
			{
				texture = new Texture();
				texture->data_ = data;
				texture->width_ = width;
				texture->height_ = height;
				texture->nrChannels_ = nrChannels;
				textures_[path] = texture;

				sprite = new graphics::Sprite(data  , width ,  height, nrChannels);
				sprite->set_name(path);
			}
			else
			{
				sprite = new graphics::Sprite();
				ENGINE_ERR_LOG("Failed to load image");
			}
		}

		

		return  sprite;
#endif
		}


		TextureLoader::~TextureLoader(){
	
#ifdef USE_SDL
			for (auto &itr : textures_) {

				SDL_FreeSurface(itr.second);
				#ifdef TEST_MODE
					ENGINE_LOG("DEstroying the SDL_Surface");
				#endif // TEST_MODE
			}
#else
			for (auto &itr : textures_) {

				stbi_image_free(itr.second->data_);
				delete itr.second;
#ifdef TEST_MODE
				ENGINE_LOG("DEstroying the Textures");
#endif // TEST_MODE
			}
#endif
			textures_.clear();

			#ifdef TEST_MODE
				ENGINE_LOG("DEstroying the TextureLoader Manager");
			#endif // TEST_MODE

		}


	}
}
