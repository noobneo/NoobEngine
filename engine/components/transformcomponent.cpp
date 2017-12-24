
/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: transformcomponent.h
Purpose: transform component for the gameobjects used for transformations
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 16th October 2017
---------------------------------------------------------*/


#include "transformcomponent.h"
#include "gameobject.h"

#ifdef TEST_MODE
	#include "../enginelogger/enginelogger.h"
#endif // TEST_MODE
#include "rendercomponent.h"

namespace enginecore {

	namespace component {

		TransformComponent::TransformComponent() {


			owner_ = nullptr;

			scale_x_ = 1.0;
			scale_x_ = 1.0;

			math::Vector2DSet(&position_, 0.0f, 0.0f);

			rotation_ = 0.0f;



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

			RenderComponent* render = static_cast<RenderComponent*>(owner_->GetComponent(E_COMPONENT_TYPE_RENDER));
			if (render) {

				render->UpdateRenderPosition(position_);
			}
		}

		void TransformComponent::SetPositionY(float _y) {

			position_.y_ = _y;
			math::Vector2DSet(&position_, position_.x_, position_.y_);

			
			RenderComponent* render = static_cast<RenderComponent*>(owner_->GetComponent(E_COMPONENT_TYPE_RENDER));
			if (render) {

				render->UpdateRenderPosition(position_);
			}
		}

		void TransformComponent::SetPosition(math::Vector2D position) {

			math::Vector2DSet(&position_, position.x_, position.y_);
		}

		void TransformComponent::HandleEvent(events::Event *event) {


		}

		void TransformComponent::UpdateProperties() {

			SetScaleX(scale_x_);
			SetScaleY(scale_y_);
			SetPosition(owner_->get_position());
		}

		TransformComponent::~TransformComponent() {

#ifdef DESTRUCTOR_LOG_MODE
			ENGINE_LOG("Destroying Transform Component ");
#endif // TEST_MODE
		}


		void TransformComponent::SetRotation(float rotate) {

			
			RenderComponent* render = static_cast<RenderComponent*>(owner_->GetComponent(E_COMPONENT_TYPE_RENDER));
			render->SetRotation(rotate);
			rotation_ = rotate;
		}



		void  TransformComponent::SetScaleX(float scale_x) {

			scale_x_ = scale_x;
			RenderComponent* render = static_cast<RenderComponent*>(owner_-> GetComponent(E_COMPONENT_TYPE_RENDER));

			if (render) {

				render->SetScaleX(scale_x);
			}
		}


		void  TransformComponent::SetScaleY(float scale_y) {


			scale_y_ = scale_y;
			RenderComponent* render = static_cast<RenderComponent*>(owner_->GetComponent(E_COMPONENT_TYPE_RENDER));

			if (render) {

				render->SetScaleY(scale_y);
			}
		}



		void TransformComponent::Reset() {

			owner_ = nullptr;
			active_ = false;
			scale_x_ = 1.0;
			scale_x_ = 1.0;
			rotation_ = 0.0f;
			math::Vector2DSet(&position_, 0.0f, 0.0f);
		}

	}

}

