#ifndef _BULLET_COMPONENT_H_
#define _BULLET_COMPONENT_H_


/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: bulletcomponent.h
Purpose: bullet behaviour component
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 16th October 2017
---------------------------------------------------------*/


#include "maincomponent.h"
#include "../maths/vector2D.h"
#include <string>


namespace enginecore {

	namespace component {

		class ComponentManager;
		class ObjectFactory;
		class BodyComponent;

		class BulletComponent : public MainComponent
		{
		public:

			void Fired(float click_x, float click_y, float speed, float start_posx, float start_posy);
		private:
			virtual void Update();
			virtual void Init(GameObject* owner);

			BulletComponent();
			~BulletComponent();
			BulletComponent(const BulletComponent&) = delete;
			BulletComponent & operator=(const BulletComponent&) = delete;

			void set_time_out(float time_out) { time_out_ = time_out; };
			void set_damage(int damage) { damage_ = damage; };

			virtual void Reset();
			virtual void HandleEvent(events::Event *event);
			virtual void UpdateProperties();

			void DestroySelf();

			
		private:
			friend class ComponentManager;
			friend class ObjectFactory;

			bool is_destroyed_;
			float time_out_;
			int damage_;
			BodyComponent* body_;
		};

	}
}

#endif // _BULLET_COMPONENT_H_
