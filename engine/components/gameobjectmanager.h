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
#include <unordered_map>

namespace enginecore {

	namespace component {

	class GameObject;

	class GameobjectManager
	{

	public:

		void Update();
		void Destroy();

		void DeleteGameobject(int id);

		static GameObject* CreateGameObject();
		static GameobjectManager* GetInstance();

	private:
		GameobjectManager();
		~GameobjectManager() = default;

		//delete copy constructor and assignment operator
		GameobjectManager& operator=(const GameobjectManager&) = delete;
		GameobjectManager(const GameobjectManager&) = delete;

		void PoolGameObjects();
		void ClearPool();


#ifdef TEST_MODE

		void IteratePool();
#endif // TEST_MODE


	private:

		static GameobjectManager* instance_;
		
		int gameobject_id_;
		int count_;

		std::unordered_map<int, GameObject*> gameobjects_;

		GameObject* first_available_;
	};

	}
}

#endif