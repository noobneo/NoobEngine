#ifndef _WEAPON_COMPONENT_H_
#define _WEAPON_COMPONENT_H_

/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: weaponcomponent.h
Purpose: weapon component for the gamobjects . has posibilities for different settings
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 16th October 2017
---------------------------------------------------------*/


#include "maincomponent.h"
#include "../maths/vector2D.h"
#include "../../external/SDL2.0 Lib/include/SDL_stdinc.h"
#include <vector>


/*Support for Long Range Related Weapons 
No Melee*/

namespace enginecore {

	namespace component {

		class ComponentManager;
		class ObjectFactory;
		class GameObject;
		class TransformComponent;
		class BodyComponent;

		typedef struct Bullets {

			Bullets() {

				bullet_ = nullptr;
				next_ = nullptr;
			}
			GameObject* bullet_;
			Bullets* next_;
		}Bullets;

		class WeaponComponent : public MainComponent
		{

		public:
			void UpdateProperties();


			void Aim(float target_x, float target_y, float weapon_x, float weapon_y);
			void Fire(float x, float y);
			void SetBody();
			virtual void Detach();
			inline bool get_can_shoot() { return can_shoot_; };
		private:
			virtual void Update();

			virtual void Init(GameObject* owner);
			void RegisterKeyBoardListener();
			void OnKeyPressed(const Uint8 * key_state);
			void OnKeyReleased(const Uint8 * key_state);
			

			void DisableShooting();
			void AddBulletToPool(GameObject* bullet);
			GameObject* FindBullet();
			void Equip(GameObject* player);
			void Throw();
			void Recoil(float x, float y);
			void Reload();
			
			WeaponComponent();
			~WeaponComponent();
			WeaponComponent(const WeaponComponent&) = delete;
			WeaponComponent& operator=(const WeaponComponent&) = delete;
			
			void SetAutoMode(bool auto_mode) ;

			inline void set_listen_mouse(bool listen_mouse) { listen_mouse_ = listen_mouse; };
			inline void set_can_shoot(bool can_shoot) { can_shoot_ = can_shoot; };
			inline void set_throw_force(float throw_force) { throw_force_ = throw_force; };
			inline void set_recoil(int recoil) { recoil_ = recoil; };
			inline void set_damage(int  damage) { damage_ = damage; };
			inline void set_mag_size(int mag_size) { mag_size_ = mag_size; };
			inline void set_fire_rate(float  fire_rate) { fire_rate_ = fire_rate; };
			inline void set_has_mouse_controller(bool has_mouse_controller) { has_mouse_controller_ = has_mouse_controller; };
			inline void set_is_equipped(bool is_equipped) { is_equipped_ = is_equipped; };
			inline void set_spray_rate(int spray_rate) { spray_rate_ = spray_rate; };
			inline void set_bullet_speed(float bullet_speed) { bullet_speed_ = bullet_speed; };
			inline void set_reload_time(float reload_time) { reload_time_ = reload_time; };
			inline void set_is_launcher(bool is_launcher) { is_launcher_ = is_launcher; };
			virtual void Reset();
			virtual void HandleEvent(events::Event *event);
			
		private:
			friend class ComponentManager;
			friend class ObjectFactory;

			bool need_reload_;
			float reload_time_;
			bool listen_mouse_;
			bool auto_mode_;
			int mag_size_;
			float bullet_speed_;
			int recoil_;
			float fire_rate_;
			int spray_rate_;
			int damage_;
			bool has_mouse_controller_;
			bool is_equipped_;
			bool can_shoot_;

			float throw_force_;

			std::vector<Bullets*> bullets_;

			std::vector<Bullets*> active_bullets_;

			Bullets* available_bullet_;
			BodyComponent* body_;
			bool is_launcher_;

		};

	}
}
#endif // !_WEAPON_COMPONENT_H_
