#ifndef _BODY_COMPONENT_H_
#define _BODY_COMPONENT_H_

#include "maincomponent.h"
#include "../maths/vector2D.h"

namespace enginecore {

	namespace component {


		typedef enum {

			E_BODY_TYPE_STATIC=1,
			E_BODY_TYPE_DYNAMIC,
			E_BODY_TYPE_KINEMATIC,

		}BodyType;

		class ComponentManager;
		class ObjectFactory;

		class BodyComponent : public MainComponent
		{

		public:

			inline void set_mass(float mass) { mass_ = mass; };
			inline void set_type(BodyType type) { type_ = type; };
			inline void set_position(math::Vector2D position) { position_ = position; };
			inline void set_veclocity(math::Vector2D veclocity) { veclocity_ = veclocity; };

			inline float get_mass() { return mass_ ; };
			inline math::Vector2D get_position() { return position_ ; };
			inline math::Vector2D get_veclocity() { return veclocity_ ; };
			inline BodyType get_type() { return type_ ; };


		private:
			BodyComponent();
			~BodyComponent()=default;

			virtual void Update();
			virtual void Init(GameObject* owner);

		private:
			friend class ComponentManager;
			friend class ObjectFactory;

			float mass_;
			math::Vector2D position_;
			math::Vector2D veclocity_;

			BodyType type_;

		};
	}
}

#endif // !_BODY_COMPONENT_H_
