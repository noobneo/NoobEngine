#include "bodycomponent.h"
#include "../physics/physicsmanager.h"
#include "gameobject.h"

namespace enginecore {


	namespace component {

		BodyComponent::BodyComponent() {
			
			math::Vector2DSet(&force_, 0.0f, 0.0f);
			math::Vector2DSet(&position_, 0.0f, 0.0f);
			math::Vector2DSet(&velocity_, 0.0f, 0.0f);
			math::Vector2DSet(&acceleration_, 0.0f, 0.0f);
			math::Vector2DSet(&prev_position_, 0.0f, 0.0f);
			mass_ = 0.0f;
			type_ = physics::E_BODY_TYPE_STATIC;
			owner_ = nullptr;
			inverse_mass_ = 0.0;
			shape_component_ = nullptr;
		}
	

		void BodyComponent::Update() {


		}


		void BodyComponent:: ApplyForceX(float force_x) {


			force_.x_ += force_x*PTM;
		}


		void BodyComponent::ApplyForceY(float force_y) {

			force_.y_ += force_y*PTM;
		}


		void BodyComponent::Integerate(float dt) {

			//dt = (float) 0.01667f;
			//calculate force
			force_.y_ += physics::PhysicsManager::GetInstance()->get_gravity();


			//calculate acceleration
			acceleration_.x_ = force_.x_ * inverse_mass_;
			acceleration_.y_ = force_.y_ * inverse_mass_;

			//calculate velcoty

			velocity_.x_ = acceleration_.x_*dt + velocity_.x_;
			velocity_.y_ = acceleration_.y_*dt + velocity_.y_;

			//store previous position
			math::Vector2DSet(&prev_position_ ,position_.x_,position_.y_) ;

			//FRICTION 

			//change position
			math::Vector2DScaleAdd(&position_, &velocity_, &prev_position_, dt);


			math::Vector2DScale(&velocity_, &velocity_, 0.99f);
			//update position
		//	owner_->SetPosition(position_);

			//clear forces
			math::Vector2DSet(&force_, 0.0f, 0.0f);

		}

		void BodyComponent::UpdatePosition() {

			//update position
			owner_->SetPosition(position_);
		}

		void BodyComponent::Init(GameObject* owner) {
			
			owner_ = owner;

			if (type_ == physics::E_BODY_TYPE_STATIC) {

				mass_ = 0.0f;
			}


			if (mass_) {

				inverse_mass_ = 1.0f / mass_;
			}
			else {

				inverse_mass_ = 0.0f;
			}
		}


		void BodyComponent:: Reset() {

			math::Vector2DSet(&force_, 0.0f, 0.0f);
			math::Vector2DSet(&position_, 0.0f, 0.0f);
			math::Vector2DSet(&velocity_, 0.0f, 0.0f);
			math::Vector2DSet(&acceleration_, 0.0f, 0.0f);
			math::Vector2DSet(&prev_position_, 0.0f, 0.0f);
			mass_ = 0.0f;
			type_ = physics::E_BODY_TYPE_STATIC;
			owner_ = nullptr;
			inverse_mass_ = 0.0;
			shape_component_ = nullptr;

		}

	}
}