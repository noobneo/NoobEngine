#ifndef _BUTTON_COMPONENT_H_
#define _BUTTON_COMPONENT_H_


/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: buttoncomponent.h
Purpose: button behaviour component
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
		

		class ButtonComponent : public MainComponent
		{
		public:


			inline void set_file_to_open(std::string file_to_open) { file_to_open_ = file_to_open; };

		private:
			virtual void Update();
			virtual void Init(GameObject* owner);

			ButtonComponent();
			~ButtonComponent();
			ButtonComponent(const ButtonComponent&) = delete;
			ButtonComponent & operator=(const ButtonComponent&) = delete;

			virtual void Reset();
			virtual void HandleEvent(events::Event *event);
			virtual void UpdateProperties();
			
			void RegisterForMouseEvent();
			void MouseEvent(uint32_t type, int x, int y);

			bool CheckIfInBounds(int x, int y);
			void ButtonPressed();



		private:
			friend class ComponentManager;
			friend class ObjectFactory;

			bool button_down_;
			bool button_up_;
		

			float max_x;
			float max_y;
			float min_x;
			float min_y;

			std::string file_to_open_;

		};

	}
}

#endif // _BUTTON_COMPONENT_H_
