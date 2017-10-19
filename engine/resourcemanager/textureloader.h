#ifndef _TEXTURE_H
#define _TEXTURE_H_

#include <unordered_map>
#include <string>
#include "../../SDL2.0 Lib/include/SDL.h"

namespace enginecore{

	namespace resourcemanager {

		//forward declaration
		class Sprite;
		class ResourceManager;

		class TextureLoader
		{

		private:
			Sprite* CreateTexture(std::string path);
		
			TextureLoader();
			~TextureLoader();
			
		private:
			std::unordered_map<std::string, SDL_Surface*> textures_;
			friend class ResourceManager;
		};
	}
}

#endif // !_TEXTURE_H
