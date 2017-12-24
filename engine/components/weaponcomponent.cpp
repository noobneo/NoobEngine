

/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: weaponcomponent.cpp
Purpose: weapon component for the gamobjects . has posibilities for different settings
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 16th October 2017
---------------------------------------------------------*/



#include "weaponcomponent.h"
#include "../enums.h"
#include "../event/eventmanager.h"
#include "../inputhandler/inputhandler.h"
#include "../inputhandler/keyboardlistener.h"
#include "../common/macros.h"
#include "mousecomponent.h"
#include "bulletcomponent.h"
#include "../maths/math-common.h"
#include "../event/event.h"

#ifdef TEST_MODE
#include "../enginelogger/enginelogger.h"
#endif // TEST_MODE

#include <string>
#include "transformcomponent.h"
#include "bodycomponent.h"
#include "rendercomponent.h"
#include "homingmissile.h"

namespace enginecore {

	namespace component {

		WeaponComponent::WeaponComponent() {

			need_reload_ = false;

			reload_time_ = 2.0f;
			listen_mouse_ = false;
			auto_mode_ = false;
			body_ = nullptr;
			can_shoot_ = false;
			is_equipped_ = false;
			owner_ = nullptr;
			fire_rate_ = 1.0;
			spray_rate_ = 1;
			mag_size_ = 10;
			recoil_ = 0;
			damage_ = 5;
			bullet_speed_ = 50.0f;
			has_mouse_controller_ = false;
			throw_force_ = 90.0f;
			available_bullet_ = nullptr;
			bullets_.clear();
			active_bullets_.clear();
			is_launcher_ = false;
		}

		void WeaponComponent::Init(GameObject* owner) {

			owner_ = owner;

			events::EventManager::GetInstance()->SubscribeComponentToEvent(events::E_EVENT_PLAYERHIT, this);
			
			RegisterKeyBoardListener();

		}

		void WeaponComponent::Update() {


		}


		void  WeaponComponent::UpdateProperties() {

			MouseComponent* ms = static_cast<MouseComponent* > (owner_->GetComponent(E_COMPONENT_TYPE_MOUSE));


			if (ms) {

				ms->set_follow_mouse(is_equipped_);
			}

			if (is_equipped_) {

				
				events::EventManager::GetInstance()->SubscribeComponentToEvent(events::E_EVENT_ENABLE_SHOOT, this);
				events::EventManager::GetInstance()->SubscribeComponentToEvent(events::E_EVENT_DETATCH, this);
				events::EventManager::GetInstance()->SubscribeComponentToEvent(events::E_MOUSE_CLICKEVENT, this);
			}
			else {
				
				events::EventManager::GetInstance()->SubscribeComponentToEvent(events::E_EVENT_TIMEDEVENT, this);
				events::EventManager::GetInstance()->UnscribeThisComponent(events::E_EVENT_ENABLE_SHOOT, this);
				events::EventManager::GetInstance()->UnscribeThisComponent(events::E_EVENT_DETATCH, this);
				events::EventManager::GetInstance()->UnscribeThisComponent(events::E_MOUSE_CLICKEVENT, this);
			}
		}

		void WeaponComponent::RegisterKeyBoardListener() {

			auto keyboard_listener = inputhandler::KeyboardListener::CreateListener();

			keyboard_listener->on_key_pressed_ = FUNCTION_CALLBACK(WeaponComponent::OnKeyPressed, this);
			keyboard_listener->on_key_released_ = FUNCTION_CALLBACK(WeaponComponent::OnKeyReleased, this);

		}

		void WeaponComponent::Detach() {

			owner_->SetActive(false);
			Throw();
			UpdateProperties();
		}


		void WeaponComponent::OnKeyPressed(const Uint8 * key_state) {

			if (!active_) {
				return;
			}

		}

		void WeaponComponent::SetAutoMode(bool auto_mode) {

			if (auto_mode) {

				auto_mode_ = auto_mode;
				events::EventManager::GetInstance()->SubscribeComponentToEvent(events::E_EVENT_RELOAD_OBJECT, this);
				events::EventManager::GetInstance()->SubscribeComponentToEvent(events::E_EVENT_TIMEDEVENT, this);
				events::EventManager::GetInstance()->SubscribeComponentToEvent(events::E_EVENT_ENABLE_SHOOT, this);
				events::EventManager::GetInstance()->SubscribeComponentToEvent(events::E_EVENT_DETATCH, this);
		
			}
		}

		void WeaponComponent::OnKeyReleased(const Uint8 * key_state) {

			if (auto_mode_) {

				return;
			}

			if (inputhandler::InputHandler::GetInstance()->IsKeyPressed(SDL_SCANCODE_G)) {

				Throw();
				UpdateProperties();
			}
			else if (inputhandler::InputHandler::GetInstance()->IsKeyPressed(SDL_SCANCODE_R)) {

				if (is_equipped_) {

					Reload();
					events::Event re;
					re.set_type(events::E_RELOAD_DONE);
					events::EventManager::GetInstance()->SendEvent(&re);
				}
			}
		}


		void WeaponComponent::Equip(GameObject* player) {

			if (is_equipped_) {

				return;
			}

			listen_mouse_ = true;
			can_shoot_ = true;
			set_is_equipped(true);
			BodyComponent * body = static_cast<BodyComponent*>(owner_->GetComponent(E_COMPONENT_TYPE_BODY));

			UpdateProperties();
			//body->set_position(owner_->get_position());
			body->set_is_physics_on(false);
			owner_->set_parent(player);
			SetBody();

		}

		void WeaponComponent::SetBody() {

			BodyComponent* parentbody = static_cast<BodyComponent*>(owner_->get_parent()->GetComponent(E_COMPONENT_TYPE_BODY));

			if (parentbody) {

				body_ = parentbody;
			}
		}

		void WeaponComponent::Throw() {

			if (!is_equipped_) {

				return;
			}

			listen_mouse_ = false;
			can_shoot_ = false;
			set_is_equipped(false);
			BodyComponent * body = static_cast<BodyComponent*>(owner_->GetComponent(E_COMPONENT_TYPE_BODY));


			body->set_positionX(owner_->get_parent()->get_position_x() );

			body->set_positionY(owner_->get_parent()->get_position_y() );
				
			body->ApplyForceX(throw_force_);
			body->ApplyForceY(throw_force_);
			body->set_is_physics_on(true);
			owner_->SetRotation(0);
			owner_->set_parent(nullptr);
			body_ = nullptr;

			events::EventManager::GetInstance()->AddTimedEvent(events::E_EVENT_TIMEDEVENT, 1.0f);
			//events::EventManager::GetInstance()->SubscribeComponentToEvent(events::E_EVENT_PLAYERHIT, this);
		}

		void WeaponComponent::Reset() {



			if (auto_mode_) {

				events::EventManager::GetInstance()->UnscribeThisComponent(events::E_EVENT_RELOAD_OBJECT, this);
			}


			is_launcher_ = false;
			reload_time_ = 1.0f;
			need_reload_ = false;
			listen_mouse_ = false;
			auto_mode_ = false;
			body_ = nullptr;
			can_shoot_ = false;
			active_ = false;
			is_equipped_ = false;
			owner_ = nullptr;
			fire_rate_ = 1.0;
			spray_rate_ = 1;
			mag_size_ = 10;
			bullet_speed_ = 50.0f;
			recoil_ = 0;
			damage_ = 5;
			has_mouse_controller_ = false;
			throw_force_ = 90.f;

			for (unsigned int i = 0; i < bullets_.size(); i++) {

				delete bullets_[i];
			}

			bullets_.clear();
			active_bullets_.clear();
			available_bullet_ = nullptr;

			events::EventManager::GetInstance()->UnscribeThisComponent(events::E_EVENT_PLAYERHIT, this);
			events::EventManager::GetInstance()->UnscribeThisComponent(events::E_EVENT_TIMEDEVENT, this);
			events::EventManager::GetInstance()->UnscribeThisComponent(events::E_EVENT_ENABLE_SHOOT, this);
			events::EventManager::GetInstance()->UnscribeThisComponent(events::E_EVENT_DETATCH, this);

		}

		void WeaponComponent::HandleEvent(events::Event *event) {
			
			if (!active_) {
				return;
			}

			if (event->get_type() == events::E_EVENT_PLAYERHIT) {

				events::EventManager::GetInstance()->UnscribeThisComponent(events::E_EVENT_PLAYERHIT, this);
				events::Event *ev = (event);
				if (ev->get_other()->get_id() == owner_->get_id())	{
					Equip(ev->get_player());
				}

			}
 			else if (event->get_type() == events::E_EVENT_TIMEDEVENT) {
				events::EventManager::GetInstance()->SubscribeComponentToEvent(events::E_EVENT_PLAYERHIT, this);
				events::EventManager::GetInstance()->UnscribeThisComponent(events::E_EVENT_TIMEDEVENT, this);
			
			}
			else if (event->get_type() == events::E_EVENT_RELOAD_OBJECT) {

				events::Event *re = (event);
				if (re->get_object_id() == get_id() && auto_mode_&& !can_shoot_) {

					Reload();
				}
			}
			else if (event->get_type() == events::E_MOUSE_CLICKEVENT && listen_mouse_) {

				events::Event *ev = (event);
				/////
				float x1 = owner_->get_position_x();
				float y1 = owner_->get_position_y();

				Aim(ev->get_x() , ev->get_y() , x1 , y1);

				if (can_shoot_) {
						Fire(ev->get_x(), ev->get_y());
				}
			}
			else if (event->get_type() == events::E_EVENT_ENABLE_SHOOT && event->get_object_id() == get_id()) {

				can_shoot_ = true;
			}
			else if (event->get_type() == events::E_EVENT_DETATCH && event->get_owner_id() == owner_->get_parent()->get_id()) {

				Detach();
				events::EventManager::GetInstance()->SubscribeComponentToEvent(events::E_EVENT_PLAYERHIT, this);
			}
		}

		void WeaponComponent::Aim(float target_x, float target_y , float weapon_x , float weapon_y) {

			float rotate = maths::ConvertToDegrees(maths::GetAngle((target_x - weapon_x), (target_y - weapon_y)));
			owner_->SetRotation(rotate);
		}

		void WeaponComponent::DisableShooting() {

			can_shoot_ = false;
			events::Event *es = new events::Event();
			es->set_object_id(get_id());
			es->set_type(events::E_EVENT_ENABLE_SHOOT);
			es->set_time(fire_rate_);
			events::EventManager::GetInstance()->AddTimedEvent(es);
		}
		
		void WeaponComponent::Fire(float x , float y) {
			
			if (!can_shoot_) {
				
				return;
			}


			GameObject*obj = FindBullet();

			if (auto_mode_ && need_reload_) {
				events::Event *re = new events::Event();
				re->set_type(events::E_EVENT_RELOAD_OBJECT);
				re->set_object_id(get_id());
				re->set_time(reload_time_);
				events::EventManager::GetInstance()->AddTimedEvent(re);
			}
			else if (!auto_mode_ && need_reload_) {

				events::Event re ;
				re.set_type(events::E_RELOAD);
				events::EventManager::GetInstance()->SendEvent(&re);
			}

			if (fire_rate_ > 0) {

				DisableShooting();
			}

			if (obj) {

				if (is_launcher_) {


					HomingMissile * missile = static_cast<HomingMissile*> (obj->GetComponent(E_COMPONENT_HOMMING_MISSILE));
					if (missile) {

						//Recoil(x, y);
						missile->Fired( owner_->get_position_x(), owner_->get_position_y());
					}


				}
				else {


					BulletComponent * bullet = static_cast<BulletComponent*> (obj->GetComponent(E_COMPONENT_TYPE_BULLET));
					if (bullet) {

						Recoil(x, y);
						bullet->Fired(x , y ,bullet_speed_ , owner_->get_position_x(), owner_->get_position_y());
					}
				}
			}
		}

		void WeaponComponent::Recoil(float x , float y) {
		

			float _x = body_->get_position().x_ - x;
			float _y = body_->get_position().y_ - y;

			math::Vector2D recoil;
			math::Vector2D pushback;
			math::Vector2DSet(&pushback, _x, _y);
			math::Vector2DNormalize(&recoil, &pushback);

			float forcex = recoil_*recoil.x_;
			float forcey = recoil_*recoil.y_;

			forcex = forcex <= enginecore::EngineConfig::config_->max_recoil_ ? forcex : enginecore::EngineConfig::config_->max_recoil_;
			forcey = forcey <= enginecore::EngineConfig::config_->max_recoil_ ? forcey : enginecore::EngineConfig::config_->max_recoil_;
/*
#ifdef TEST_MODE
			ENGINE_LOG("forcex : %.2f", forcex);
			ENGINE_LOG("forcey : %.2f", forcey);
#endif // TEST_MODE*/


			body_->ApplyForceX(forcex);
			body_->ApplyForceY(forcey);
		}


		void WeaponComponent::Reload() {

			for (auto itr : active_bullets_) {

				itr->next_ = available_bullet_;
				available_bullet_ = itr;
				available_bullet_->bullet_->SetActive(false);
			}
			active_bullets_.clear();
			need_reload_ = false;
		}

		void WeaponComponent::AddBulletToPool(GameObject* bulletobj) {

			Bullets * bullet = new Bullets();
			bullet->next_ = nullptr;
			bullet->bullet_ = nullptr;

			bullet->bullet_ = bulletobj;
			bullet->next_ = available_bullet_;
			available_bullet_ = bullet;
			bullets_.push_back(bullet);
		}

		GameObject* WeaponComponent::FindBullet() {

			if (!available_bullet_) {

				need_reload_ = true;
			//	ENGINE_LOG("EMpty Reload");
				return nullptr;
				//Reload();
			}

			active_bullets_.push_back(available_bullet_);
			GameObject* obj = available_bullet_->bullet_;
			available_bullet_ = available_bullet_->next_;

			return obj;
		}


		WeaponComponent::~WeaponComponent() {

			Reset();
		}
	}
}

