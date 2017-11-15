#ifndef _SHAPE_COMPONENT_H_
#define _SHAPE_COMPONENT_H_

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
			virtual void Init(GameObject* owner);
			virtual void Reset();

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
