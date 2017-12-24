#ifndef _HOMINGMISSILE_COMPONENT_H_
#define _HOMINGMISSILE_COMPONENT_H_


/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: hommingmissile.h
Purpose: homing behaviour for the missiles
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 16th October 2017
---------------------------------------------------------*/


#include "maincomponent.h"
#include "../enums.h"


namespace enginecore {
	namespace events {

		class Event;
	}
}

namespace enginecore {

	namespace component {

		class GameObject;
		class Shape;
		class BodyComponent;
		class TransformComponent;

		class HomingMissile : public MainComponent
		{



		public:

			void Fired(float start_posx, float start_posy);
			inline void set_rotation_speed(float rotation_speed) { rotation_speed_ = rotation_speed; };
			inline void set_speed(float speed) { speed_ = speed; };
			inline void set_target_name(std::string target_name) { target_name_ = target_name; };

		private:
			HomingMissile();
			~HomingMissile() ;

			void DestroySelf();

			virtual void Update();
			virtual void Reset();
			virtual void Init(GameObject* owner);
			virtual void HandleEvent(events::Event *event);

			virtual void UpdateProperties();


		private:
			friend class ComponentManager;
			friend class ObjectFactory;

			BodyComponent* body_component_;
			TransformComponent* transform_;

			bool is_destroyed_;
			int damage_;
			float rotation_speed_;
			float speed_;
			std::string target_name_;
			GameObject* target_;
		};
	}
}

#endif //_HOMINGMISSILE_COMPONENT_