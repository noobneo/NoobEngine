#ifndef _TEXTURE_H
#define _TEXTURE_H_

#include <unordered_map>
#include <string>
#include "../../SDL2.0 Lib/include/SDL_surface.h"
#include "../../SDL2.0 Lib/include/SDL_video.h"
#include "../graphics/sprite.h"

namespace enginecore{

	namespace resourcemanager {

		/*
		* @brief: texture data
		*/
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

			/*
			* @function : CreateTexture(std::string path)
			* @param: path is the filepath of the texture 
			* @return: returns the newly sprite created
			* @brief: creates and returns the sprite created with the texture.  Also stores the 
			* texture in a map.
			*/
			graphics::Sprite* CreateTexture(std::string path);
		
			//ctor
			TextureLoader();

			//dtor
			~TextureLoader();
			
		private:
			std::unordered_map<std::string, Texture *> textures_;
			friend class ResourceManager;
		};
	}
}

#endif // !_TEXTURE_H
