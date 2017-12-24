
/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: rendercomponent.cpp
Purpose: renders component for the gameobjects
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 16th October 2017



---------------------------------------------------------*/

#include "rendercomponent.h"
#include "transformcomponent.h"
#include "gameobject.h"
#ifdef TEST_MODE
#include "../enginelogger/enginelogger.h"
#endif // TEST_MODE
#include "../graphics/sprite.h"
#include "../event/event.h"
#include "../event/eventmanager.h"

namespace enginecore {

	namespace component {

		RenderComponent::RenderComponent() {

			image_ = nullptr;
			transform_component_ref_ = nullptr;
			previous_alpha_ = 1.0f;
		}

		RenderComponent::~RenderComponent()	{

			active_ = false;
			image_ = nullptr;
#ifdef DESTRUCTOR_LOG_MODE
			ENGINE_LOG("Destroying RenderCOmpoenent");
#endif // TEST_MODE
		}

		void RenderComponent::Init(GameObject* owner) {

			owner_ = owner;
			transform_component_ref_ = static_cast<TransformComponent*>(owner_->GetComponent(E_COMPONENT_TYPE_TRANSFORM));
			events::EventManager::GetInstance()->SubscribeComponentToEvent(events::E_BLINK_EVENT , this);

			//init with default image
		}

		void RenderComponent::UpdateRenderPosition(math::Vector2D position) {

			//image_->SetPositionX(position.x_);
			//image_->SetPositionY(position.y_);

			image_->SetPosition(position.x_, position.y_);
		}

		void RenderComponent::Update() {
			if (!active_) {
				return;
			}
			UpdateRenderPosition(transform_component_ref_->get_position());
		}

		void RenderComponent::HandleEvent(events::Event *event) {


			if (event->get_type() == events::E_BLINK_EVENT) {

				SetBlink(false);
			}
			
		}



		void RenderComponent::Reset() {

			previous_alpha_ = 1.0f;
			active_ = false;
			image_ = nullptr;
			transform_component_ref_ = nullptr;

		}


		void RenderComponent::SetFlip(float flip_x, float flip_y) {

			image_->SetFlip(flip_x, flip_y);
		}

		void RenderComponent:: UpdateProperties() {
			
			image_->UpdateProperties(owner_->GetComponent(E_COMPONENT_TYPE_DEBUG_DRAW));
			//SetSize(owner_->get_width(), owner_->get_height());
		}

		void RenderComponent::SetRotation(float rotate) {
			
	
		//	image_->SetFlipX(1.0);
			//transform_component_ref_->set_rotation(rotate);
			image_->set_rotate(rotate);

		}


		void RenderComponent::SetBlink(bool blink) {

			if (!image_->get_alpha()) {

				return;
			}
			if (blink) {

				previous_alpha_ = image_->get_alpha();
				image_->set_alpha(.2f);

				events::Event *ev= new events::Event();
				ev->set_type(events::E_BLINK_EVENT);
				ev->set_time(.05f);
				events::EventManager::GetInstance()->AddTimedEvent(ev);

			}
			else {

				image_->set_alpha(1.0f);
			}
		}
#ifdef TEST_MODE
		void RenderComponent::LeftRotate() {

			image_->LeftRotation();
		}
		void RenderComponent::RightRotate() {

			image_->RightRotation();
		}


#endif // TEST_MODE

		void RenderComponent::set_active(bool active) {

			active_ = active;
			image_->set_active(active);
		}

	}
}

