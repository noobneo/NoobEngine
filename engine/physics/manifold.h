#ifndef _MANIFOLD_H_
#define _MANIFOLD_H_

#include "../components/bodycomponent.h"
#include "../maths/vector2D.h"

namespace enginecore {

	namespace physics {


		struct Contact {

			//math::Vector2D position;
			math::Vector2D normal;
			float penetration;
		};

		class Manifold
		{
		public:
			Manifold();
			~Manifold()=default;

			void ApplyImpulse();
			void PositionCorrection();
		
		public:
			component::BodyComponent* body1_;
			component::BodyComponent* body2_;
		
			Contact contacts_;

		};

	}
}

#endif // !_MANIFOLD_H_
