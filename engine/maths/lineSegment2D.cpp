
/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: LineSegment2D.cpp
Purpose: Vector2D class which builds the line segment
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 ,x86  .Windows
Project: CS529_ajaytanwar_2
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: October 4th 2017
---------------------------------------------------------*/

#include "lineSegment2D.h"

namespace enginecore {

	namespace math {

		int BuildLineSegment2D(LineSegment2D *LS, Vector2D *Point0, Vector2D *Point1)
		{

			/*if (Vector2DSquareDistance(&Point0 , &Point1)<EPSILON) {

			//return not a line segment
			return 0;
			}*/

			Vector2D edge, normal_to_edge;

			//edge vector
			Vector2DSub(&edge, Point0, Point1);

			//normal to edge
			Vector2DSet(&normal_to_edge, -edge.y_, edge.x_);

			//normalize
			Vector2DNormalize(&normal_to_edge, &normal_to_edge);

			//dot product to see if the point lies on the normal
			LS->normal_dot_point0_ = Vector2DDotProduct(&normal_to_edge, Point0);

			Vector2DSet(&LS->line_normal_, normal_to_edge.x_, normal_to_edge.y_);
			Vector2DSet(&LS->point0_, Point0->x_, Point0->y_);
			Vector2DSet(&LS->point1_, Point1->x_, Point1->y_);

			return 1;

		}

	}
}
