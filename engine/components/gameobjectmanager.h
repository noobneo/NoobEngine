#ifndef _GAME_OBJECT_MANAGER_H_
#define _GAME_OBJECT_MANAGER_H_

/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: gameobjectmanager.h
Purpose: game object manager which is a singleton class which helps in managing the gameobjects
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 25th October 2017
---------------------------------------------------------*/
#include <array>
#include <unordered_map>
#include "component-types.h"

namespace enginecore {

	namespace component {

	class GameObject;
	class ComponentManager;

	class GameobjectManager
	{

	public:

		void Update();
		void Destroy();

		void AddRenderComponent(GameObject* game_object);
		void AddPhysicsComponent(GameObject* game_object);
		void AddTransformComponent(GameObject* game_object);

		void DeleteGameobject(int id);
		GameObject* CreateGameObject();

		static GameobjectManager* GetInstance();

	private:
		GameobjectManager();
		~GameobjectManager() = default;

		//delete copy constructor and assignment operator
		GameobjectManager& operator=(const GameobjectManager&) = delete;
		GameobjectManager(const GameobjectManager&) = delete;

		void ClearPool();
		void PoolGameObjects();
		void InitComponentManager();

#ifdef TEST_MODE
		void IteratePool();
#endif // TEST_MODE


	private:

		static GameobjectManager* instance_;
		
		int gameobject_id_;
		int count_;

		std::array<GameObject*,MAX_SIZE> gameobjects_;
		std::unordered_map<int,GameObject*> active_objects_;

		GameObject* first_available_;
		ComponentManager* component_manager_;
	};

	}
}

#endif
