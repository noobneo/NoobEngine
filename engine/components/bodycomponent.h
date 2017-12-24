#ifndef _BODY_COMPONENT_H_
#define _BODY_COMPONENT_H_


/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: bodycomponent.h
Purpose: body component for gameobject
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 16th October 2017
---------------------------------------------------------*/


#include "maincomponent.h"
#include "../maths/vector2D.h"
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

			void UpdateMass();
			void ResetForces();
			void ResetBody();

			inline bool get_is_bullet() { return is_bullet_; ; }
			inline void set_is_bullet(bool is_bullet) { is_bullet_ = is_bullet; }
			inline void set_mass(float mass) { mass_ = mass; };
			inline void set_type(physics::BodyType type) { type_ = type; };
			inline void set_position(math::Vector2D position) { position_ = position; };
			inline void set_velocity(math::Vector2D velocity) { velocity_ = velocity; };
			inline void set_velocityX(float x) { velocity_.x_ = x; };
			inline void set_velocityY(float y) { velocity_.y_ = y; };
			inline void set_positionX(float x) { position_.x_ = x; };
			inline void set_positionY(float y) { position_.y_ = y; };
			inline void set_gravity_scale(float gravity_scale) { gravity_scale_ = gravity_scale; };
			inline void set_collision_tag(int collision_tag) { collision_tag_ = collision_tag; };
			inline float get_mass() { return mass_ ; };
			inline float get_inverse_mass() { return inverse_mass_; };
			inline void set_is_physics_on(bool is_physics_on) { is_physics_on_ = is_physics_on; };

			inline bool get_is_physics_on() { return is_physics_on_ ; };
			inline float get_gravity_scale() { return gravity_scale_; };
			inline math::Vector2D get_position() { return position_ ; };
			inline math::Vector2D get_velocity() { return velocity_; };
			inline physics::BodyType get_type() { return type_ ; };
			inline int get_collision_tag() { return collision_tag_; };
			inline ShapeComponent* get_shape_component() { return shape_component_; };

		private:
			BodyComponent();
			~BodyComponent();

			virtual void Update();
			virtual void Reset();
			virtual void Init(GameObject* owner);
			virtual void HandleEvent(events::Event *event);
			void set_shape_component(ShapeComponent* shape_component) { shape_component_ = shape_component; };

		private:
			friend class ComponentManager;
			friend class ObjectFactory;
		//	friend class PhysicsManager;

			
			bool once_;
			bool is_physics_on_;
			int collision_tag_;
			float friction_;
			float mass_;
			float inverse_mass_;
			float gravity_scale_;

			physics::BodyType type_;

			math::Vector2D force_;
			math::Vector2D position_;
			math::Vector2D velocity_;
			math::Vector2D acceleration_;
			math::Vector2D prev_position_;
		
			ShapeComponent* shape_component_;
			bool is_bullet_;

		};
	}
}

#endif // !_BODY_COMPONENT_H_
