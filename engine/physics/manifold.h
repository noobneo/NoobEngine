#ifndef _MANIFOLD_H_
#define _MANIFOLD_H_

#include "../components/bodycomponent.h"
#include "../maths/vector2D.h"

namespace enginecore {

	namespace physics {


		/*
		* @brief: structure to store the contact information
		*/
		struct Contact {

			//math::Vector2D position;
			math::Vector2D normal;
			float penetration;
		};

		class Manifold
		{
		public:
			//ctor
			Manifold();
			
			//dtor
			~Manifold()=default;

			/*
			* @function : ApplyImpulse()
			* @brief: applies impulse to the colliding bodies
			*/
			void ApplyImpulse();
			
			/*
			* @function : PositionCorrection()
			* @brief: This method peforms position correction on touch bodies to avoid
			* merging of bodies
			*/
			void PositionCorrection();
		
		public:
			component::BodyComponent* body1_;
			component::BodyComponent* body2_;
		
			Contact contacts_;

		};

	}
}

#endif // !_MANIFOLD_H_
