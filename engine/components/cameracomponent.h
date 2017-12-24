#ifndef _CAMERA_COMPONENT_H_
#define _CAMERA_COMPONENT_H_



/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: cameracomponent.h
Purpose: camera for the side scrolling
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 16th October 2017
---------------------------------------------------------*/


#include "maincomponent.h"
#include "../maths/vector2D.h"
#include "../maths/mat4.h"

namespace enginecore {
	//viewpoert store
	//update matrix based on that
	namespace component {

		class ComponentManager;
		class ObjectFactory;
		class TransformComponent;

		class CameraComponent : public MainComponent
		{

		private:
			virtual void Update();
			virtual void Init(GameObject* owner);

			CameraComponent();
			~CameraComponent();
			CameraComponent(const CameraComponent&) = delete;
			CameraComponent& operator=(const CameraComponent&) = delete;

			virtual void Reset();
			virtual void HandleEvent(events::Event *event);
			virtual void UpdateProperties();

			maths::Mat4& get_view() { return view_; };
		private:
			friend class ComponentManager;
			friend class ObjectFactory;

			math::Vector2D view_port_;
			math::Vector2D view_offset_;
			TransformComponent* transform_;
			maths::Mat4 view_;
		};

	}
}

#endif // _ANIMATION_COMPONENT_H_
