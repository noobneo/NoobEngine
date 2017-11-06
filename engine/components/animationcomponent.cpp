#include "animationcomponent.h"
#include "gameobject.h"
#include "transformcomponent.h"

#ifdef TEST_MODE
	#include "../enginelogger/enginelogger.h"
#endif // TEST_MODE

namespace enginecore {

	namespace component {

		AnimationComponent::AnimationComponent() {

			owner_ = nullptr;
			direction_ = "y";
			limit_ = 200;
			step_ = 5.0f;
			current_step_ = 0.0;
			dir_ = 1;
		}


		AnimationComponent::~AnimationComponent() {
#ifdef TEST_MODE
			ENGINE_LOG("Destroying AnimationComponent ");
#endif // TEST_MODE
		}


		void AnimationComponent::Update() {

			TransformComponent* transform_comp = static_cast<TransformComponent*>(owner_->GetComponent(E_COMPONENT_TYPE_TRANSFORM));
			
			if (current_step_ <= limit_) {

				current_step_ += step_;
				if(direction_ == "y")
					transform_comp->SetPositionY(transform_comp->get_position_y() + step_*dir_);
				else 
					transform_comp->SetPositionX(transform_comp->get_position_x() + step_*dir_);
			}
			else {

				current_step_ = 0;
				dir_ *= -1;
			}
		}

		void AnimationComponent::Init(GameObject* owner) {

			owner_ = owner;
		}

	}
}
