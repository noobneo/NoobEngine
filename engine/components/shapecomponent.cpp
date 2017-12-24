
/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: shapecomponent.cpp
Purpose: shape component for the gameobjects used for collision purpose
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 16th October 2017
---------------------------------------------------------*/


#include "shapecomponent.h"
#include "../physics/physicsmanager.h"

namespace enginecore {

	namespace component {


		ShapeComponent::ShapeComponent(){

			shape_type_ = physics::E_SHAPE_AABB;
			shape_ = nullptr;// physics::PhysicsManager::GetInstance()->GetShape(shape_type_);
			body_component_ = nullptr;
		} 

		void ShapeComponent::Update() {


		}

		void ShapeComponent::Init(GameObject* owner) {

			owner_ = owner;
			shape_ = physics::PhysicsManager::GetInstance()->GetShape(shape_type_);
		}

		void ShapeComponent::AddShape(physics::ShapeType type) {

			if (type != shape_type_) {

				physics::PhysicsManager::GetInstance()->RemoveShape(shape_);
				shape_type_ = type;
				shape_ = physics::PhysicsManager::GetInstance()->GetShape(shape_type_);
			}

		}

		void ShapeComponent::SetShapeAttribs(float radius) {
			
			shape_->set_radius(radius);
		}

		void ShapeComponent::SetShapeAttribs(float width, float height) {

			shape_->set_dimensions(width , height);
		}

		void ShapeComponent::HandleEvent(events::Event *event) {


		}



		void ShapeComponent::Reset() {

			active_ = false;
			physics::PhysicsManager::GetInstance()->RemoveShape(shape_);
			shape_type_ = physics::E_SHAPE_AABB;
			shape_ = nullptr;
			body_component_ = nullptr;

		}

	}
}
