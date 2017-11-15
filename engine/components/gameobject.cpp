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

#include "gameobject.h"
#include "gameobjectmanager.h"
#include "../enginelogger/enginelogger.h"
#include "maincomponent.h"
#include "transformcomponent.h"
#include "../fpscontroller/fpscontroller.h"

namespace enginecore {

	namespace component {

		GameObject::GameObject() {

			id_			= -1;
			next_		= nullptr;
			is_active_	= false;
			math::Vector2DSet(&position_, 0.0f, 0.0f);
			tag_ = "";
			width_ = 0.0f;
			height_ = 0.0f ;
			jump_force_ = 0.0f;
			max_speed_ = 0.0f;
			move_force_ = 0.0f;
		}

		void GameObject::Update(){

		}

		void GameObject::AttachComponent(MainComponent * component, ComponentType type) {

			auto itr = components_.find(type);

			if (itr != components_.end()) {

				ENGINE_ERR_LOG("Component already attached ! Make sure you remove it first to add different");
				return;
			}
			components_[type] = component;
		}

		void GameObject::SetPositionX(float position_x) {

			TransformComponent* transform = static_cast<TransformComponent*>(GetComponent(E_COMPONENT_TYPE_TRANSFORM));

			position_.x_ = position_x;
			//TransformComponent* trans = static_cast<TransformComponent*> ();
			transform->SetPositionX(position_x);
		}

		void GameObject::SetPosition(math::Vector2D position) {

			TransformComponent* transform = static_cast<TransformComponent*>(GetComponent(E_COMPONENT_TYPE_TRANSFORM));
			transform->SetPosition(position);

		}

		void GameObject::SetPositionY(float position_y) {

			TransformComponent* transform = static_cast<TransformComponent*>(GetComponent(E_COMPONENT_TYPE_TRANSFORM));

			position_.y_ = position_y;
			//TransformComponent* trans = static_cast<TransformComponent*> ();
			transform->SetPositionY(position_y);
		}

		MainComponent* GameObject::GetComponent(ComponentType type) {

			auto itr = components_.find(type);

			if (itr != components_.end()) {

				return itr->second;
			}

			ENGINE_ERR_LOG("Could not find the component with type : %d", type);

			return NULL;
		}


		void GameObject::Reset() {

			components_.clear();
			is_active_ = false;
			tag_ = "";
			width_ = 0.0f;
			height_ = 0.0f;
			jump_force_ = 0.0f;
			max_speed_ = 0.0f;
			move_force_ = 0.0f;
			math::Vector2DSet(&position_, 0.0f, 0.0f);
		}


		GameObject::~GameObject() {


#ifdef TEST_MODE
		//	ENGINE_LOG("Destroying Gameobject :%d",id_);
#endif // TEST_MODE
			
			components_.clear();
			id_ = -1;
			next_ = nullptr;
			is_active_ = false;
			tag_ = "";
			width_ = 0.0f;
			height_ = 0.0f;
			jump_force_ = 0.0f;
			max_speed_ = 0.0f;
			move_force_ = 0.0f;
		}


	}
}
