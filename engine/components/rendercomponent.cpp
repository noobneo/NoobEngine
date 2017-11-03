#include "rendercomponent.h"

namespace enginecore {

	namespace component {

		RenderComponent::RenderComponent() {

			image_ = nullptr;
		}

		RenderComponent::~RenderComponent()	{

			image_ = nullptr;
		}

		void RenderComponent::Init() {

			//init with default image
		}

		void RenderComponent::UpdateRenderPosition(math::Vector2D position) {

			image_->SetPositionX(position.x_);
			image_->SetPositionY(position.y_);
		}

		void RenderComponent::Update() {

		}
	}
}

