/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: cameracomponent.cpp
Purpose: camera for the side scrolling
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 16th October 2017
---------------------------------------------------------*/



#include "cameracomponent.h"
#include "gameobject.h"
#include "transformcomponent.h"
#include "../graphics/renderer.h"


namespace enginecore {

	namespace component {

		int space = 1;

		void CameraComponent ::Update() {
	
			view_port_.x_ = view_offset_.x_ - transform_->get_position_x();
			view_port_.y_ = 0.0;// view_offset_.y_ - transform_->get_position_y();

			view_ = maths::Mat4::Translate(maths::Vec3(view_port_.x_, view_port_.y_*.5f,0.0f));
			graphics::Renderer::GetInstance()->set_camera_pos(view_port_);
			graphics::Renderer::GetInstance()->set_view(view_);

		}

		void CameraComponent::Init(GameObject* owner) {

			owner_ = owner;
		
		}

		CameraComponent::CameraComponent() {

			view_port_.x_ = 0.0f;
			view_port_.y_ = 0.0f;
			view_ = maths::Mat4(1.0);
		}


		void CameraComponent::UpdateProperties() {
	
			transform_ = static_cast<TransformComponent*>(owner_->GetComponent(E_COMPONENT_TYPE_TRANSFORM));
			math::Vector2DSet(&view_offset_, owner_->get_position_x(), owner_->get_position_y());
		}

		CameraComponent ::~CameraComponent() {

			Reset();
		}
	
		void CameraComponent::Reset() {

			math::Vector2DSet(&view_offset_, 0.0,0.0);
			math::Vector2DSet(&view_port_, 0.0, 0.0);
			view_ = maths::Mat4(1.0);
		}

		void CameraComponent::HandleEvent(events::Event *event) {


		}
	}
}
