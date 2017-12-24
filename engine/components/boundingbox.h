#ifndef _BOUNDINGBOX_COMPONENT_H_
#define _BOUNDINGBOX_COMPONENT_H_
/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: boundingbox.h
Purpose: bounding box for debug mode
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 16th October 2017


---------------------------------------------------------*/


#include "maincomponent.h"
#include "../maths/vec2.h"
#include "../maths/mat4.h"

namespace enginecore {

	namespace component {

		class ComponentManager;
		class ObjectFactory;
		class TransformComponent;

		class BoundingBoxComponent : public MainComponent
		{


			void SetColor(float r, float g, float b , float a);

			inline void set_bound_width(int bound_width) { bound_width_ = bound_width; };
			inline void set_bound_height(int bound_height) { bound_height_ = bound_height; };


			inline void set_anchorpoint_x(float x) { anchorpoint_.set_x(x); };
			inline void set_anchorpoint_y(float y) { anchorpoint_.set_y(y); };

		
		private:
			virtual void Update();
			virtual void Init(GameObject* owner);

			BoundingBoxComponent();
			~BoundingBoxComponent();
			BoundingBoxComponent(const BoundingBoxComponent &) = delete;
			BoundingBoxComponent  & operator=(const BoundingBoxComponent &) = delete;


			virtual void Reset();
			virtual void HandleEvent(events::Event *event);

			void LoadMesh();
		
		public:

			void DrawShape();
			
			void ConstructBuffers(unsigned int &vbo);

			virtual void UpdateProperties();

		private:
			friend class ComponentManager;
			friend class ObjectFactory;

			TransformComponent* transform_;
			int bound_width_;
			int bound_height_;

			maths::Mat4 ml_matrix_;
		//	maths::Mat4 ml_matrix_1_;
			maths::Vec2 anchorpoint_;

			unsigned int vbo_;
			//unsigned int line_;
			unsigned int cbo_;
			float r_;
			float g_;
			float b_;
			float a_;		
		};

	}
}

#endif // _BODY_ANIMATION_COMPONENT_H_
