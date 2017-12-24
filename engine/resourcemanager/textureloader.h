#ifndef _TEXTURE_H
#define _TEXTURE_H_

#include <unordered_map>
#include <string>
#include "../../SDL2.0 Lib/include/SDL_surface.h"
#include "../../SDL2.0 Lib/include/SDL_video.h"
#include "../graphics/sprite.h"

namespace enginecore{

	namespace resourcemanager {


		typedef struct Texture {

			int width_;
			int height_;
			int nrChannels_;
			unsigned char*data_;

		}Texture;

		//forward declaration

		class ResourceManager;

		class TextureLoader
		{

		private:
			graphics::Sprite* CreateTexture(std::string path);
		
			TextureLoader();
			~TextureLoader();
			
		private:
			std::unordered_map<std::string, Texture *> textures_;
			friend class ResourceManager;
		};
	}
}

#endif // !_TEXTURE_H
