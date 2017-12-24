#ifndef _HEALTH_COMPONENT_H_
#define _HEALTH_COMPONENT_H_

/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: healthcomponent.h
Purpose: adds health attribute to the gameobject
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 16th October 2017
---------------------------------------------------------*/


#include "maincomponent.h"

namespace enginecore {
	namespace events {

		class EventManager;
	}
}

namespace enginecore {

	namespace component {

		class ComponentManager;
		class ObjectFactory;
		class BodyComponent;
		class GameObject;

		class HealthComponent : public MainComponent
		{

	
		private:
			virtual void Update();
			virtual void Init(GameObject* owner);

			HealthComponent();
			~HealthComponent();
			HealthComponent(const HealthComponent &) = delete;
			HealthComponent  & operator=(const HealthComponent &) = delete;

			virtual void Reset();
			virtual void HandleEvent(events::Event *event);

			void set_health(int health) { health_ = health; };

		private:
			friend class ComponentManager;
			friend class ObjectFactory;

			BodyComponent* transform_;
			int health_;

		};

	}
}

#endif // _HEALTH_COMPONENT_H_
