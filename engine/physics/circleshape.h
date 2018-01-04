#ifndef _CIRCLE_SHAPE_H_
#define _CIRCLE_SHAPE_H_

#include "shape.h"

namespace enginecore {

	namespace physics {

		class CircleShape : public Shape
		{
		public:
			//ctor
			CircleShape() = default;
			CircleShape(ShapeType type);
			//dtor
			~CircleShape();

			/*
			* @function : Reset()
			* @brief: Resets the properties of the shape
			*/
			virtual void Reset();
			/*
			* @function : set_radius(float radius)
			* @brief: sets the radius of the circle shape
			*/
			 virtual void set_radius(float radius) { radius_ = radius; };

			 //getter for the radius
			 inline float get_radius() { return radius_; };
		private:
			float radius_;
		};
	}
}


#endif // !_CIRCLE_SHAPE_H_
