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


		void ShapeComponent::Reset() {

			physics::PhysicsManager::GetInstance()->RemoveShape(shape_);
			shape_type_ = physics::E_SHAPE_AABB;
			shape_ = nullptr;
			body_component_ = nullptr;

		}

	}
}
