#ifndef  _OBJECT_FACTORY_H_
#define _OBJECT_FACTORY_H_


/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: objectfactory.h
Purpose: object factory creates gameobjects
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 16th October 2017



---------------------------------------------------------*/
#include "../serializer/serialized-data.h"
#include <unordered_map>

#include <vector>
namespace enginecore {

	namespace component {

		class GameObject;

		class ObjectFactory
		{

		public :

			static ObjectFactory* GetInstance();
			void CreateObjectsFromGameData(std::vector<GameObjectData> &leveldata);
			void CreateObjects(std::vector<GameObjectData> &leveldata, std::vector<GameObject*>& created_objects);
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
