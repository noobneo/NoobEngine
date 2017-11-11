#include "bodycomponent.h"



namespace enginecore {


	namespace component {

		BodyComponent::BodyComponent() {
			
			math::Vector2DSet(&position_, 0.0f, 0.0f);
			math::Vector2DSet(&veclocity_, 0.0f, 0.0f);
			mass_ = 0.0f;
			type_ = E_BODY_TYPE_STATIC;
			owner_ = nullptr;
	
		}
	

		void BodyComponent::Update() {


		}


		void BodyComponent::Init(GameObject* owner) {
			
			owner_ = owner;

		}

	}
}