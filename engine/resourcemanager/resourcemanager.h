#ifndef _RESOURCE_MANAGER_H_
#define _RESOURCE_MANAGER_H_
#include <unordered_map>


namespace enginecore {

	namespace resourcemanager {

		class ResourceManager
		{

		public:
			static ResourceManager* GetInstance();

			//create a class to wrap textures
			SDL_Surface* CreateSprite(std::string path);
			void Destroy();

		private:
			ResourceManager() = default;
			~ResourceManager() = default;


		private:

			static ResourceManager* instance_;
			std::unordered_map<std::string, SDL_Surface*> textures_;

		};
	}

}


#endif // !_RESOURCE_MANAGER_H_
