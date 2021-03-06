#ifndef _MAIN_COMPONENT_H_
#define _MAIN_COMPONENT_H_

/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: maincomponent.h
Purpose: base component class from which other components inherit
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 25th October 2017
---------------------------------------------------------*/

#include "component-types.h"

namespace enginecore {

	namespace events {

		class Event;
	}
}

namespace enginecore {

	namespace component {

		class GameObject;
		class ComponentManager;

		class MainComponent
		{

		public:
			ComponentType get_component_type() { return component_type_; };
			void set_component_type(ComponentType component_type) { component_type_ = component_type; };

			GameObject* get_owner() { return owner_; };
			void set_owner(GameObject* owner) { owner_ = owner; };

			void set_next(MainComponent* next) { next_= next; };
			MainComponent* get_next() { return next_; };

			virtual void HandleEvent(events::Event *event) = 0;

			void set_id(int id) { id_ = id; };
			int get_id() { return id_; };

			virtual void set_active(bool active) { active_ = active; };
			virtual bool get_active() { return active_; };

			virtual void Update() = 0;
			virtual void Init(GameObject* owner) = 0;

			virtual void Detach() {};
			virtual void UpdateProperties() {};

		protected:
			MainComponent();
			virtual ~MainComponent();

			virtual void Reset() = 0;

			GameObject* owner_;
		private:
			friend class ComponentManager;
			

			int id_;


			ComponentType component_type_;
			MainComponent* next_;
		protected:

			bool active_;


			
		};
	}
}

#endif // !_MAIN_COMPONENT_H_
