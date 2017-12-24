#ifndef _BODY_ANIMATION_COMPONENT_H_
#define _BODY_ANIMATION_COMPONENT_H_


/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: bodyanimationcomponent.h
Purpose: animation component for physics body
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 16th October 2017
---------------------------------------------------------*/


#include "maincomponent.h"
#include <string>


namespace enginecore {

	namespace component {

		class BodyComponent;
	}
}


namespace enginecore {

	namespace component {

		class ComponentManager;
		class ObjectFactory;

		class BodyAnimationComponent : public MainComponent
		{

		private:
			virtual void Update();
			virtual void Init(GameObject* owner);

			BodyAnimationComponent();
			~BodyAnimationComponent();
			BodyAnimationComponent(const BodyAnimationComponent&) = delete;
			BodyAnimationComponent & operator=(const BodyAnimationComponent&) = delete;


			inline void set_velocity_x(float velocity_x) { velocity_x_ = velocity_x; };
			inline void set_velocity_y(float velocity_y) { velocity_y_ = velocity_y; };
			inline void set_limit(float limit) { limit_ = limit; };
			inline void set_step(float step) { step_ = step; };
			inline void set_direction(std::string  direction) { direction_ = direction; };

			inline void set_random_limit(int random_limit) { random_limit_ = random_limit; };
			inline void set_random(bool random) { random_ = random; };

			virtual void Reset();
			virtual void HandleEvent(events::Event *event);

		private:
			friend class ComponentManager;
			friend class ObjectFactory;

			BodyComponent* body_;
			std::string direction_;
			float current_step_;
			float limit_;
			float step_;
			int dir_;
			float velocity_x_ ;
			float velocity_y_;
			bool random_;
			int random_limit_;

		};

	}
}

#endif // _BODY_ANIMATION_COMPONENT_H_
