#include "rendercomponent.h"
#include "transformcomponent.h"
#include "gameobject.h"
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

			//image_->SetPositionX(position.x_);
			//image_->SetPositionY(position.y_);

			image_->SetPosition(position.x_, position.y_);
		}

		void RenderComponent::Update() {

			TransformComponent* transform_comp = static_cast<TransformComponent*>(owner_->GetComponent(E_COMPONENT_TYPE_TRANSFORM));
			UpdateRenderPosition(transform_comp->get_position());
		}
	}
}

