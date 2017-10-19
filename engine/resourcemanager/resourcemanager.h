#ifndef _RESOURCE_MANAGER_H_
#define _RESOURCE_MANAGER_H_
#include <string>

namespace enginecore {

	namespace resourcemanager {

		class Sprite;
		class TextureLoader;

		class ResourceManager
		{

		public:
			static ResourceManager* GetInstance();

			//create a class to wrap textures
			Sprite* CreateSprite(std::string path);
			void Destroy();

		private:
			ResourceManager();
			~ResourceManager();


		private:

			static ResourceManager* instance_;
			
			TextureLoader* texture_loader_;
		};
	}

}


#endif // !_RESOURCE_MANAGER_H_
