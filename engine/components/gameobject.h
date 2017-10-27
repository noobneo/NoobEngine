#ifndef _GAME_OBJECT_H
#define _GAME_OBJECT_H


/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: gameobject.h
Purpose: its a game object class 
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 25th October 2017
---------------------------------------------------------*/
#include <unordered_map>
#include "component-types.h"

namespace enginecore {

	namespace component {

	class MainComponent;

	class GameObject 
	{

	public:
		virtual void Update();

		int get_id() { return id_; };
		void set_id(int id) {  id_  = id; };
		
	private:
		GameObject() :components_(MAX_SIZE){}
		~GameObject();
		GameObject& operator=(const GameObject&) = delete;
		GameObject(const GameObject&) = delete;

		//void Init(int id);

		void set_next(GameObject* next) { next_ = next; };
		void set_is_active(bool is_active) { is_active_ = is_active; };

		bool get_is_active() { return is_active_; };
		GameObject* get_next() { return next_; };

	private:
		friend class GameobjectManager;

		int id_;
		bool is_active_;
		
		std::unordered_map<ComponentType, MainComponent*> components_;
		
		GameObject* next_;
	};

	}

}

#endif

