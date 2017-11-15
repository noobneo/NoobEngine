#include "transformcomponent.h"
#include "gameobject.h"

#ifdef TEST_MODE
	#include "../enginelogger/enginelogger.h"
#endif // TEST_MODE

namespace enginecore {

	namespace component {

		TransformComponent::TransformComponent() {


			owner_ = nullptr;

			scale_x_ = 1.0;
			scale_x_ = 1.0;

			math::Vector2DSet(&position_, 0.0f, 0.0f);


		}


		void TransformComponent::Update() {


		}

		void TransformComponent::Init(GameObject* owner) {

			owner_ = owner;

			scale_x_ = 1.0;
			scale_x_ = 1.0;

			math::Vector2DSet(&position_, 0.0f, 0.0f);
		}

		void TransformComponent::SetPositionX(float _x) {

			position_.x_ = _x;
			math::Vector2DSet(&position_, position_.x_, position_.y_);
		}

		void TransformComponent::SetPositionY(float _y) {

			position_.y_ = _y;
			math::Vector2DSet(&position_, position_.x_, position_.y_);
		}

		void TransformComponent::SetPosition(math::Vector2D position) {

			math::Vector2DSet(&position_, position.x_, position.y_);
		}


		TransformComponent::~TransformComponent() {

#ifdef TEST_MODE
			ENGINE_LOG("Destroying Transform Component ");
#endif // TEST_MODE
		}

		void TransformComponent::Reset() {

			owner_ = nullptr;

			scale_x_ = 1.0;
			scale_x_ = 1.0;

			math::Vector2DSet(&position_, 0.0f, 0.0f);
		}

	}

}

