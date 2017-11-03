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
	class ComponentManager;

	class GameObject 
	{

	public:
		void Update();
		
		int get_id() { return id_; };
		void set_id(int id) {  id_  = id; };
		
		void SetPositionX(float position_x);
		void SetPositionY(float position_y);

		MainComponent* GetComponent(ComponentType type);
		//template <typename T>
		//T GetComponent(ComponentType type);
		
		inline float get_position_x() { return position_x_; };
		inline float get_position_y() { return position_y_; };


	private:
		GameObject();
		~GameObject();
		GameObject& operator=(const GameObject&) = delete;
		GameObject(const GameObject&) = delete;

		//void Init(int id);

		void AttachComponent(MainComponent * component, ComponentType type);

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

		float position_x_;
		float position_y_;

		int width_;
		int height_;


	};

	}

}

#endif

