/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: gameobject.h
Purpose: its a game object class
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 25th October 2017
---------------------------------------------------------*/

#include "gameobject.h"
#include "gameobjectmanager.h"
#include "../enginelogger/enginelogger.h"
#include "maincomponent.h"
#include "transformcomponent.h"
#include "../fpscontroller/fpscontroller.h"
#include "rendercomponent.h"
#include "bodycomponent.h"
#include "weaponcomponent.h"
#include "../event/event.h"
#include "../event/eventmanager.h"
#include "../common/scenemanager.h"
#include "../event/event.h"
#include "../particlemanager/particlemanager.h"

namespace enginecore {

	namespace component {

		GameObject::GameObject() {

			id_			= -1;
			next_		= nullptr;
			parent_ = nullptr;
			math::Vector2DSet(&position_, 0.0f, 0.0f);
			tag_ = "";
			width_ = 50.0f;
			height_ = 50.0f ;
			jump_force_ = 0.0f;
			max_speed_ = 0.0f;
			move_force_ = 0.0f;
			offset_x_ = 10.0f;
			active_ = false;
			offset_y_ = 10.0f;
		}

		void GameObject::Update(){

			if (!active_) {
				return;
			}

			if (parent_) {

				SetFlip();
				SetPosition(parent_->get_position());
			}

			//playlogic
			if (get_tag() == "player") {

				if (position_.y_ < 0) {

					events::Event ev;
					ev.set_type(events::E_GAMEOVER);
					events::EventManager::GetInstance()->SendEvent(&ev);
				}

			}

		}

		void GameObject::AttachComponent(MainComponent * component, ComponentType type) {

			auto itr = components_.find(type);

			if (itr != components_.end()) {

				ENGINE_ERR_LOG("Component already attached ! Make sure you remove it first to add different");
				return;
			}
			components_[type] = component;
		}

		void GameObject::SetPositionX(float position_x) {

			TransformComponent* transform = static_cast<TransformComponent*>(GetComponent(E_COMPONENT_TYPE_TRANSFORM));

			position_.x_ = position_x;

			if (parent_) {
				position_.x_ += offset_x_;
				position_.y_ += offset_y_;

			}
			//TransformComponent* trans = static_cast<TransformComponent*> ();
			transform->SetPositionX(position_x);
		}


		void GameObject::SetFlip() {

			if (parent_) {

				RenderComponent* parent = static_cast<RenderComponent*>(parent_->GetComponent(E_COMPONENT_TYPE_RENDER));
				RenderComponent* self = static_cast<RenderComponent*>(GetComponent(E_COMPONENT_TYPE_RENDER));

				self->SetFlip(parent->get_flip_x(), parent->get_flip_y());
			}
		}


		void GameObject::SetPosition(math::Vector2D position) {


			if (!active_) {
				return;
			}
			//temp;
			if (parent_) {
			//	RenderComponent* render = static_cast<RenderComponent*>(GetComponent(E_COMPONENT_TYPE_RENDER));
				position.x_ += offset_x_;
				position.y_ += offset_y_;
			}

			TransformComponent* transform = static_cast<TransformComponent*>(GetComponent(E_COMPONENT_TYPE_TRANSFORM));
			position_ = position;
			transform->SetPosition(position);
		}

		void GameObject::SetPositionY(float position_y) {

			TransformComponent* transform = static_cast<TransformComponent*>(GetComponent(E_COMPONENT_TYPE_TRANSFORM));

			position_.y_ = position_y;
			if (parent_) {
				position_.y_ += offset_y_;
			}

			//TransformComponent* trans = static_cast<TransformComponent*> ();
			transform->SetPositionY(position_y);
		}

		MainComponent* GameObject::GetComponent(ComponentType type) {

			auto itr = components_.find(type);

			if (itr != components_.end()) {

				return itr->second;
			}

		//	ENGINE_ERR_LOG("Could not find the component with type : %d", type);

			return NULL;
		}


		void GameObject::HandleEvent(events::Event* event) {

			if (get_tag() == "game_state_manager") {

 				switch (event->get_type()) {

				case events::E_GAMEOVER:
					common::SceneManager::GetInstance()->LoadScene("gameover");
					break;

				case events::E_MAINMENU:
					common::SceneManager::GetInstance()->LoadScene("mainmenu");
					break;

				case events::E_GAMEWIN:
					common::SceneManager::GetInstance()->LoadScene("gamewin");
				break;


				case events::E_RESTART:
					common::SceneManager::GetInstance()->LoadLastLevel();
					break;

				case events::E_NEXT_LEVEL :
					events::EventManager::GetInstance()->UnscribeThisGameObject( events::E_NEXT_LEVEL,this);
					common::SceneManager::GetInstance()->NextLevel();
					break;

				}
			}

			else if (event->get_type() == events::E_PLAYER_DEATH) {

				events::Event *gameover = new events::Event();
				gameover->set_type(events::E_GAMEOVER);
				gameover->set_time(1.5f);
				events::EventManager::GetInstance()->AddTimedEvent(gameover);
			}


			else if (event->get_type() == events::E_BOSS_DEATH) {

				events::Event *gameover = new events::Event();
				gameover->set_type(events::E_GAMEWIN);
				gameover->set_time(1.5f);
				events::EventManager::GetInstance()->AddTimedEvent(gameover);
			}



			else if (event->get_type() == events::E_RELOAD_DONE) {

				SetActive(false);
			}

			else if (event->get_type() == events::E_RELOAD) {

				SetPositionX(GameobjectManager::GetInstance()->GetGameObjectByTag("player")->get_position_x());
				SetActive(true);
			}


			else {

				for (auto &itr : components_) {

					itr.second->HandleEvent(event);
				}
			}
		}

		void GameObject::UpdateComponentProperties(bool active) {
			
			if (parent_) {
				position_.x_ += offset_x_;
				position_.y_ += offset_y_;
			}
			/*TransformComponent* transform = static_cast<TransformComponent*>(GetComponent(E_COMPONENT_TYPE_TRANSFORM));
			transform->SetPosition(position_);*/

			
		/*	RenderComponent* render = static_cast<RenderComponent*>(GetComponent(E_COMPONENT_TYPE_RENDER));
			render->SetSize(width_, height_);*/
			for (auto & it : components_) {

				it.second->UpdateProperties();
			}
		
			SetActive(active);
		}

		void GameObject::SetRotation(float rotate) {
			TransformComponent* transform = static_cast<TransformComponent*>(GetComponent(E_COMPONENT_TYPE_TRANSFORM));
			transform->SetRotation(rotate);
		}

		void GameObject::FlipX() {
			RenderComponent* render = static_cast<RenderComponent*>(GetComponent(E_COMPONENT_TYPE_RENDER));
			if (render) {

				render->FlipX();
			}

			SetFlip();
		}

		void GameObject::FlipY() {

			RenderComponent* render = static_cast<RenderComponent*>(GetComponent(E_COMPONENT_TYPE_RENDER));
			if (render) {

				render->FlipY();
			}

			SetFlip();
		}

		void GameObject::SetFlipX(float flip_x) {

			RenderComponent* render = static_cast<RenderComponent*>(GetComponent(E_COMPONENT_TYPE_RENDER));
			if (render) {

				render->set_flip_x(flip_x);
			}

			SetFlip();
		}

		void GameObject::SetFlipY(float flip_y) {

			RenderComponent* render = static_cast<RenderComponent*>(GetComponent(E_COMPONENT_TYPE_RENDER));
			if (render) {

				render->set_flip_y(flip_y);
			}
			SetFlip();
		}


		void  GameObject::SetScaleX(float scale_x) {

			TransformComponent* transform = static_cast<TransformComponent*>(GetComponent(E_COMPONENT_TYPE_TRANSFORM));

			transform->SetScaleX(scale_x);
		}


		void  GameObject::SetScaleY(float scale_y) {

			TransformComponent* transform = static_cast<TransformComponent*>(GetComponent(E_COMPONENT_TYPE_TRANSFORM));
			transform->SetScaleY(scale_y);
		}


		void GameObject::Reset() {

			parent_ = nullptr;
			components_.clear();
			active_ = false;
			tag_ = "";
			width_ = 0.0f;
			height_ = 0.0f;
			jump_force_ = 0.0f;
			max_speed_ = 0.0f;
			move_force_ = 0.0f;
			offset_x_ = 50.0f;
			offset_y_ = 0.0f;
			math::Vector2DSet(&position_, 0.0f, 0.0f);
		}

		void GameObject::SetActive(bool active) {

			active_ = active;
			for (auto & it : components_) {

				it.second->set_active(active);
			}
		}

		void GameObject::Die() {

			SetRotation(90);
			for (auto & it : components_) {

				//if (it.first != E_COMPONENT_TYPE_TRANSFORM  && it.first != E_COMPONENT_TYPE_BODY  && it.first != E_COMPONENT_TYPE_RENDER && it.first != E_COMPONENT_TYPE_DEBUG_DRAW) {
					
					it.second->Detach();
					it.second->set_active(false);
			//	}
			}

			events::Event detatch;
			detatch.set_type(events::E_EVENT_DETATCH);
			detatch.set_owner_id(get_id());
			events::EventManager::GetInstance()->SendEvent(&detatch);

			particlesystem::ParticleManager::GetInstance()->GenerateParticle(position_.x_, position_.y_, 10.0f, -50, 50,1.0,0.0,0.0);
			//particlesystem::ParticleManager::GetInstance()->GenerateParticle(position_.x_, position_.y_, 2, -10, 10);
		}
		GameObject::~GameObject() {


#ifdef DESTRUCTOR_LOG_MODE
		//	ENGINE_LOG("Destroying Gameobject :%d",id_);
#endif // TEST_MODE
			parent_ = nullptr;
			components_.clear();
			id_ = -1;
			next_ = nullptr;
			active_ = false;
			tag_ = "";
			width_ = 0.0f;
			height_ = 0.0f;
			jump_force_ = 0.0f;
			max_speed_ = 0.0f;
			move_force_ = 0.0f;
		}


	}
}
