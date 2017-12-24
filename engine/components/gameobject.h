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
#include "../maths/vector2D.h"
#include "component-types.h"

namespace enginecore {
	namespace events {

		class Event;
	}
}

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

		void SetScaleX(float scale_x);
		void SetScaleY(float scale_y);

		void SetPositionX(float position_x);
		void SetPositionY(float position_y);
		void SetRotation(float rotate);
		void FlipX();
		void FlipY();
		void SetFlipX(float flip_x);
		void SetFlipY(float flip_y);
		void SetActive(bool active);
		void Die();
		void UpdateComponentProperties(bool active_);

		MainComponent* GetComponent(ComponentType type);
		void HandleEvent(events::Event* event);
		//template <typename T>
		//T GetComponent(ComponentType type);
		
		inline math::Vector2D& get_position() { return position_; };
		inline float get_position_x() { return position_.x_; };
		inline float get_position_y() { return position_.y_; };

		inline void set_tag(std::string tag) { tag_ = tag; };
		inline std::string get_tag() { return tag_; };

		inline float get_jump_force() { return jump_force_; };
		inline float get_max_speed() { return max_speed_ ; };
		inline float get_move_force() { return move_force_ ; };
		inline GameObject* get_parent() { return parent_ ; };
		inline void set_parent(GameObject* parent) { parent_ = parent; };


		inline float get_offset_x() { return offset_x_ ; };
		inline float get_offset_y() { return  offset_y_ ; };

		inline float get_width( ) { return width_ ; };
		inline float get_height() { return height_ ; };

		inline bool get_active() { return active_; };
	private:
		GameObject();
		~GameObject();
		GameObject& operator=(const GameObject&) = delete;
		GameObject(const GameObject&) = delete;

		//void Init(int id);

		void AttachComponent(MainComponent * component, ComponentType type);

		void set_next(GameObject* next) { next_ = next; };

		GameObject* get_next() { return next_; };

		inline void set_jump_force(float jump_force) { jump_force_ = jump_force; };
		inline void set_max_speed(float max_speed)   { max_speed_ = max_speed; };
		inline void set_move_force(float move_force) { move_force_ = move_force; };
		inline void set_offset_x(float offset_x) { offset_x_ =  offset_x; };
		inline void set_offset_y(float offset_y) { offset_y_ = offset_y; };
		inline void set_width(float width) { width_ = width; };
		inline void set_height(float height) { height_ = height; };
		void Reset();
		void SetFlip();

	private:
		friend class GameobjectManager;
		friend class ObjectFactory;

		int id_;
	
		
		std::unordered_map<ComponentType, MainComponent*> components_;
		
		GameObject* next_;
		GameObject* parent_;

		math::Vector2D position_;

		float jump_force_;
		float max_speed_;
		float move_force_;
		float width_;
		float height_;
		std::string tag_;

		float offset_x_;
		float offset_y_;
		bool active_;

		MainComponent* body_;
		MainComponent* render_;
		MainComponent* transform_;

	};

	}

}

#endif

