#ifndef  _OBJECT_FACTORY_H_
#define _OBJECT_FACTORY_H_

#include "../serializer/serialized-data.h"
#include <unordered_map>

#include <vector>
namespace enginecore {

	namespace component {

		class ObjectFactory
		{

		public :

			static ObjectFactory* GetInstance();
			void CreateObjects(std::vector<GameObjectData> &leveldata);
			void Destroy();
			void ReloadLevel();

		private:
			ObjectFactory() =default;
			~ObjectFactory() = default;

			ObjectFactory(const ObjectFactory& copy) = delete;
			void operator=(const ObjectFactory& copy) = delete;

		private:

			static ObjectFactory* instance_;
			std::unordered_map<std::string , GameObjectData> level_data_;

			std::vector<GameObjectData> leveldata_;
		};


	}
}
#endif // ! _OBJECT_FACTORY_H_
