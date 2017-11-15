#ifndef _CIRCLE_SHAPE_H_
#define _CIRCLE_SHAPE_H_

#include "shape.h"

namespace enginecore {

	namespace physics {

		class CircleShape : public Shape
		{
		public:
			CircleShape() = default;
			CircleShape(ShapeType type);
			~CircleShape();

			virtual void Reset();
			 virtual void set_radius(float radius) { radius_ = radius; };

		private:
			float radius_;
		};
	}
}


#endif // !_CIRCLE_SHAPE_H_
