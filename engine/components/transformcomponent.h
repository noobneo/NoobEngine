#ifndef _TRANSFORM_COMPONENT_H_
#define _TRANSFORM_COMPONENT_H_

/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: transformcomponent.h
Purpose: transform component for the gameobjects used for transformations
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 16th October 2017
---------------------------------------------------------*/



#include "maincomponent.h"
#include "../maths/vector2D.h"

namespace enginecore {

	namespace component {

		class ComponentManager;
		class ObjectFactory;

		class TransformComponent : public MainComponent
		{

		public:

			void SetPositionX(float _x);
			void SetPositionY(float _y);

			void  SetScaleX(float scale_x);
			void  SetScaleY(float scale_y);

			void SetPosition(math::Vector2D position);
			 void SetRotation(float rotation);
			
			virtual void UpdateProperties();
			float get_position_x() { return position_.x_;};
			float get_position_y() { return position_.y_; };

			inline math::Vector2D get_position() { return position_; };

			inline float get_rotation() { return rotation_; };

			inline float get_scale_y() { return scale_y_; }
			inline float get_scale_x() { return scale_x_;}

		private:
			virtual void Update();
			virtual void Reset();
			virtual void Init(GameObject* owner);
			virtual void HandleEvent(events::Event *event);

			TransformComponent();
			~TransformComponent();

		private:
			friend class ComponentManager;
			friend class ObjectFactory;

			math::Vector2D position_;

			float scale_x_;
			float scale_y_;
			float rotation_;

		};

	}
}

#endif // !_TRANSFORM_COMPONENT_H_
