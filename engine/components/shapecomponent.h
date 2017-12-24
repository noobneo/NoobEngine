#ifndef _SHAPE_COMPONENT_H_
#define _SHAPE_COMPONENT_H_



/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: shapecomponent.h
Purpose: shape component for the gameobjects used for collision purpose
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 16th October 2017
---------------------------------------------------------*/



#include "maincomponent.h"
#include "../physics/shape.h"

namespace enginecore {

	namespace component {

		class GameObject;
		class Shape;
		class BodyComponent;

		class ShapeComponent : public MainComponent
		{

		public:

			inline physics::ShapeType get_shape_type() { return shape_type_; };
			inline physics::Shape* get_shape() { return shape_; };

		private:
			ShapeComponent();
			~ShapeComponent()=default;


			virtual void Update();
			virtual void Reset();
			virtual void Init(GameObject* owner);
			virtual void HandleEvent(events::Event *event);

			void AddShape(physics::ShapeType type);
			void SetShapeAttribs(float radius);
			void SetShapeAttribs(float width,float height);



			void set_body_component(BodyComponent* body_component) { body_component_ = body_component; };

		private:
			friend class ComponentManager;
			friend class ObjectFactory;

			physics::ShapeType shape_type_;
	
			physics::Shape* shape_;
			BodyComponent* body_component_;
	
	
		};



	}
}

#endif // !_SHAPE_COMPONENT_H_
