#ifndef _LINESEGMENT2D_H_
#define _LINESEGMENT2D_H_

#include "vector2D.h"

namespace enginecore {

	namespace math {

		typedef struct LineSegment2D {
			Vector2D point0_;		// Point on the line
			Vector2D point1_;		// Point on the line
			Vector2D line_normal_;		// Line's normal
			float normal_dot_point0_;		// To avoid computing it every time it's needed
		}LineSegment2D;


		/*
		This function builds a 2D line segment's data using 2 points
		- Computes the normal (Unit Vector)
		- Computes the dot product of the normal with one of the points

		- Parameters
		- LS:		The to-be-built line segment
		- Point0:	One point on the line
		- Point1:	Another point on the line

		- Returns 1 if the line equation was built successfully
		*/
		int BuildLineSegment2D(LineSegment2D *LS, Vector2D *Point0, Vector2D *Point1);

	}
}
#endif