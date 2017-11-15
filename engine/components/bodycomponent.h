#ifndef _BODY_COMPONENT_H_
#define _BODY_COMPONENT_H_

#include "maincomponent.h"
#include "../maths/vector2D.h"
#include "../physics/physicsmanager.h"
#include "component-types.h"

namespace enginecore {

	namespace component {


		class ComponentManager;
		class ObjectFactory;
		class ShapeComponent;
		
		class BodyComponent : public MainComponent
		{

		public:
			void Integerate(float dt);

			void UpdatePosition();
			void ApplyForceX(float force_x);
			void ApplyForceY(float force_y);
			inline void set_mass(float mass) { mass_ = mass; };
			inline void set_type(physics::BodyType type) { type_ = type; };
			inline void set_position(math::Vector2D position) { position_ = position; };
			inline void set_velocity(math::Vector2D velocity) { velocity_ = velocity; };
			inline void set_velocityX(float x) { velocity_.x_ = x; };
			inline void set_velocityY(float y) { velocity_.y_ = y; };

			inline float get_mass() { return mass_ ; };
			inline float get_inverse_mass() { return inverse_mass_; };
			inline math::Vector2D get_position() { return position_ ; };
			inline math::Vector2D get_velocity() { return velocity_; };
			inline physics::BodyType get_type() { return type_ ; };
			inline ShapeComponent* get_shape_component() { return shape_component_; };

		private:
			BodyComponent();
			~BodyComponent()=default;

			virtual void Update();
			virtual void Init(GameObject* owner);
			virtual void Reset();

			void set_shape_component(ShapeComponent* shape_component) { shape_component_ = shape_component; };


		private:
			friend class ComponentManager;
			friend class ObjectFactory;
		//	friend class PhysicsManager;

			float mass_;
			float inverse_mass_;

			physics::BodyType type_;

			math::Vector2D force_;
			math::Vector2D position_;
			math::Vector2D velocity_;
			math::Vector2D acceleration_;
			math::Vector2D prev_position_;

			ShapeComponent* shape_component_;

		};
	}
}

#endif // !_BODY_COMPONENT_H_
