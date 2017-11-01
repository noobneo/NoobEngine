#include "rendercomponent.h"
#include "../resourcemanager/sprite.h"

namespace enginecore {

	namespace component {

		RenderComponent::RenderComponent() {

			image_ = nullptr;
		}

		RenderComponent::~RenderComponent()	{

			image_ = nullptr;
		}

		void RenderComponent::Update() {


		}
	}
}

