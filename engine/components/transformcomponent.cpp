#include "transformcomponent.h"
#include "gameobject.h"

#ifdef TEST_MODE
	#include "../enginelogger/enginelogger.h"
#endif // TEST_MODE

namespace enginecore {

	namespace component {

		TransformComponent::TransformComponent() {

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
			//UpdateRenderPosition();
		}

		void TransformComponent::SetPositionY(float _y) {

			position_.y_ = _y;
			math::Vector2DSet(&position_, position_.x_, position_.y_);
		}

		void TransformComponent::SetPosition(math::Vector2D position) {

			math::Vector2DSet(&position_, position.x_, position.y_);
			//UpdateRenderPosition();
		}


		void TransformComponent::UpdateRenderPosition(){

			/*RenderComponent* render_comp = static_cast<RenderComponent*>(owner_->GetComponent(E_COMPONENT_TYPE_RENDER));
			render_comp->UpdateRenderPosition(position_);*/
		}

		TransformComponent::~TransformComponent() {

#ifdef TEST_MODE
			ENGINE_LOG("Destroying Transform Component ");
#endif // TEST_MODE
		}

	}

}

