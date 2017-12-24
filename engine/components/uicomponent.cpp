

#include "uicomponent.h"
#include "../event/event.h"


namespace enginecore {

	namespace component {


		UiComponent::UiComponent() {

			render_ = nullptr;
			owner_ = nullptr;

		}


		UiComponent::~UiComponent() {


			Reset();
		}


	
		void UiComponent::Update() {


		}


		void UiComponent::Init(GameObject* owner) {

			owner_ = owner;
		}

		void UiComponent::Reset() {

			render_ = nullptr;
			owner_ = nullptr;
		}

		void UiComponent::HandleEvent(events::Event *event) {


		}
	}
}
