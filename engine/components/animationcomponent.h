#ifndef _ANIMATION_COMPONENT_H_
#define _ANIMATION_COMPONENT_H_



/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: animationcomponent.h
Purpose: animation component
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

		class TransformComponent;
	}
}

namespace enginecore {

	namespace component {

		class ComponentManager;
		class ObjectFactory;

		class AnimationComponent : public MainComponent
		{

		private:
			virtual void Update();
			virtual void Init(GameObject* owner);

			AnimationComponent();
			~AnimationComponent();
			AnimationComponent(const AnimationComponent&) = delete;
			AnimationComponent& operator=(const AnimationComponent&) = delete;

			void set_limit(float limit) { limit_ = limit; };
			void set_step(float step) { step_ = step; };
			void set_direction(std::string  direction) { direction_ = direction; };

			virtual void Reset();
			virtual void HandleEvent(events::Event *event) ;
 
		private:
			friend class ComponentManager;
			friend class ObjectFactory;

			TransformComponent* transform_;
			std::string direction_;
			float current_step_;
			float limit_;
			float step_;
			int dir_;
			
		};

	}
}

#endif // _ANIMATION_COMPONENT_H_
