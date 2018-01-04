#ifndef _RESOURCE_MANAGER_H_
#define _RESOURCE_MANAGER_H_
#include <string>
#include "../graphics/sprite.h"

namespace enginecore {

	namespace resourcemanager {

		class Sprite;
		class TextureLoader;

		class ResourceManager
		{

		public:

			/*
			* @function : GetInstance()
			* @return: static reference to the class ResourceManager
			* @brief: creates and returns the singleton reference to the ResourceManager
			*/
			static ResourceManager* GetInstance();

			/*
			* @function : CreateSprite(std:::string path)
			* @param:path is file path of the image to be created
			* @return: a custom class sprite 
			* @brief: creates and returns the sprite created from the image file
			*/
			graphics::Sprite* CreateSprite(std::string path);
			
			/*
			* @function : Destroy()
			* @brief: deletes the reference to the ResourceManager
			*/
			void Destroy();

		private:
			//ctor
			ResourceManager();
			//dtor
			~ResourceManager();


		private:

			static ResourceManager* instance_;
			
			TextureLoader* texture_loader_;
		};
	}

}


#endif // !_RESOURCE_MANAGER_H_
