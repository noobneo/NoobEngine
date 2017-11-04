#include "rendercomponent.h"

#ifdef TEST_MODE
#include "../enginelogger/enginelogger.h"
#endif // TEST_MODE

namespace enginecore {

	namespace component {

		RenderComponent::RenderComponent() {

			image_ = nullptr;
		}

		RenderComponent::~RenderComponent()	{

			image_ = nullptr;
#ifdef TEST_MODE
			ENGINE_LOG("Destroying RenderCOmpoenent");
#endif // TEST_MODE
		}

		void RenderComponent::Init(GameObject* owner) {

			owner_ = owner;
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

