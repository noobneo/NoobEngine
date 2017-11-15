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
#include "../maths/vector2D.h"

namespace enginecore {

	namespace component {

	class MainComponent;
	class ComponentManager;
	class ObjectFactory;

	class GameObject 
	{

	public:
		void Update();
		
		int get_id() { return id_; };
		void set_id(int id) {  id_  = id; };
		
		void SetPosition(math::Vector2D position);
		void SetPositionX(float position_x);
		void SetPositionY(float position_y);

		MainComponent* GetComponent(ComponentType type);
		//template <typename T>
		//T GetComponent(ComponentType type);
		
		inline math::Vector2D get_position() { return position_; };
		inline float get_position_x() { return position_.x_; };
		inline float get_position_y() { return position_.y_; };

		void set_tag(std::string tag) { tag_ = tag; };
		std::string get_tag() { return tag_; };

		float get_jump_force() { return jump_force_; };
		float get_max_speed() { return max_speed_ ; };
		float get_move_force() { return move_force_ ; };

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

		void set_jump_force(float jump_force) { jump_force_ = jump_force; };
		void set_max_speed(float max_speed)   { max_speed_ = max_speed; };
		void set_move_force(float move_force) { move_force_ = move_force; };




		void Reset();

	private:
		friend class GameobjectManager;
		friend class ObjectFactory;

		int id_;
		bool is_active_;
		
		std::unordered_map<ComponentType, MainComponent*> components_;
		
		GameObject* next_;

		math::Vector2D position_;

		float jump_force_;
		float max_speed_;
		float move_force_;
		float width_;
		float height_;
		std::string tag_;


	};

	}

}

#endif

