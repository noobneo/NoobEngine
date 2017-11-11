#include "shapecomponent.h"



namespace enginecore {

	namespace component {


		ShapeComponent::ShapeComponent(){


		} 

		void ShapeComponent::Update() {


		}

		void ShapeComponent::Init(GameObject* owner) {

			owner_ = owner;
		}

	}
}
