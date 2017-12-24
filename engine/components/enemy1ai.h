#ifndef _ENEMYAI_COMPONENT_H_
#define _ENEMYAI_COMPONENT_H_


/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: enem1ai.h
Purpose: adds enemy behaviour provides different configuration possibilities
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 16th October 2017
---------------------------------------------------------*/



#include "maincomponent.h"

#include "../enums.h"

namespace enginecore {

	namespace component {

		class GameObject;
		class Shape;
		class BodyComponent;
		class WeaponComponent;

		class Enemy1AI : public MainComponent
		{

		private:
			Enemy1AI();
			~Enemy1AI() = default;


			inline void set_weapon(WeaponComponent* weapon) { weapon_ = weapon; };

			virtual void Update();
			virtual void Reset();
			virtual void Init(GameObject* owner);
			virtual void HandleEvent(events::Event *event);

			virtual void UpdateProperties();

			void Behave();
			void Stop();
			void Walk();
			void Attack();
			void Retrieve();
			void Jump();

			void AimPlayer();
			void Shoot();

			inline void set_is_air_borne(bool is_air_borne) { is_air_borne_ = is_air_borne; };
			inline void set_fire_speed(float fire_speed) { fire_speed_ = fire_speed; };
			inline void set_stroll_limit(int stroll_limit) { stroll_limit_ = stroll_limit; };
			inline void set_max_idle(int max_idle) { max_idle_ = max_idle; };
			inline void set_target_name(std::string target_name) { target_name_ = target_name; }
			inline void set_sensor_range_x(int sensor_range_x) { sensor_range_x_ = sensor_range_x; };
			inline void set_sensor_range_y(int sensor_range_y) { sensor_range_y_ = sensor_range_y; };

			void CheckForTarget();

			virtual void Detach();

		private:
			friend class ComponentManager;
			friend class ObjectFactory;

			BodyComponent* body_component_;

			bool is_idle_;
			bool is_air_borne_;
			int dir_;
			int counter_;
			int stroll_limit_;
			int max_idle_;
			float fire_speed_;
			EnemyState state_;
			EnemyState prev_state_;
			int sensor_range_x_;
			int sensor_range_y_;
			GameObject* target_;

			std::string target_name_;

			WeaponComponent* weapon_;
			bool can_shoot_;

		};

	}
}

#endif // !_SHAPE_COMPONENT_H_
