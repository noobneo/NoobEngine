
#ifndef _CONTROLLER_COMPONENT_H_
#define _CONTROLLER_COMPONENT_H_


/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: controllercomponent.h
Purpose: controller component for the gameobject to be controlled
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 16th October 2017
---------------------------------------------------------*/


#include "maincomponent.h"

namespace enginecore {

	namespace component {
		
		class ComponentManager;
		class ObjectFactory;
		class BodyComponent;

		class ControllerComponent : public MainComponent
		{

		private:
			ControllerComponent();
			~ControllerComponent();


			virtual void Update();
			virtual void Reset();

			virtual void Init(GameObject* owner);
			virtual void HandleEvent(events::Event *event);



			void RegisterKeyBoardListener();
			void OnKeyPressed(const uint8_t * key_state);
			void OnKeyReleased(const uint8_t * key_state);


		private:
			friend class ComponentManager;
			friend class ObjectFactory;

			BodyComponent* body_component_;
			bool is_airborne_;
			
		};
	}
}

#endif // !_CONTROLLER_COMPONENT_H_
