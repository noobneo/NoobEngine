/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Math2D.c
Purpose: Math2D class which includes implementation of Math functions for collision between different geometry
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x86,Windows
Project: CS529_ajaytanwar_2
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: September 13th 2017
---------------------------------------------------------*/

#include "math2D.h"
#include <math.h>

/*
This function checks if the point P is colliding with the circle whose
center is "Center" and radius is "Radius"
*/

namespace enginecore {

	namespace math {

		int StaticPointToStaticCircle(Vector2D *pP, Vector2D *pCenter, float Radius)
		{
			if (Vector2DSquareDistance(pP, pCenter) <= Radius * Radius) {

				return COLLISION;
			}
			return NO_COLLISION;
		}


		/*
		This function checks if the point Pos is colliding with the rectangle
		whose center is Rect, width is "Width" and height is Height
		*/
		int StaticPointToStaticRect(Vector2D *pPos, Vector2D *pRect, float Width, float Height)
		{

			float _right = pRect->x_ + Width / 2;
			float _left = pRect->x_ - Width / 2;
			float _top = pRect->y_ + Height / 2;
			float _bottom = pRect->y_ - Height / 2;

			float _x = pPos->x_;
			float _y = pPos->y_;

			if (_x > _right || _x < _left || _y > _top || _y <_bottom) {

				return NO_COLLISION;
			}

			return COLLISION;
		}

		/*
		This function checks for collision between 2 circles.
		Circle0: Center is Center0, radius is "Radius0"
		Circle1: Center is Center1, radius is "Radius1"
		*/
		int StaticCircleToStaticCircle(Vector2D *pCenter0, float Radius0, Vector2D *pCenter1, float Radius1)
		{
			if (Vector2DSquareDistance(pCenter1, pCenter0) <= (Radius0 + Radius1) * (Radius0 + Radius1)) {

				return COLLISION;
			}
			return NO_COLLISION;
		}

		/*
		This functions checks if 2 rectangles are colliding
		Rectangle0: Center is pRect0, width is "Width0" and height is "Height0"
		Rectangle1: Center is pRect1, width is "Width1" and height is "Height1"
		*/
		int StaticRectToStaticRect(Vector2D *pRect0, float Width0, float Height0, Vector2D *pRect1, float Width1, float Height1)
		{

			float r0_left = pRect0->x_ - Width0 / 2;
			float r0_right = pRect0->x_ + Width0 / 2;
			float r0_top = pRect0->y_ + Height0 / 2;
			float r0_bottom = pRect0->y_ - Height0 / 2;

			float r1_right = pRect1->x_ + Width1 / 2;
			float r1_left = pRect1->x_ - Width1 / 2;
			float r1_top = pRect1->y_ + Height1 / 2;
			float r1_bottom = pRect1->y_ - Height1 / 2;

			if (r0_left>r1_right || r0_right<r1_left || r0_top < r1_bottom || r0_bottom > r1_top) {

				return NO_COLLISION;
			}

			return COLLISION;
		}


		//////////////////////
		// New to project 2 //
		//////////////////////


		/*
		This function determines the distance separating a point from a line

		- Parameters
		- P:		The point whose location should be determined
		- LS:		The line segment

		- Returned value: The distance. Note that the returned value should be:
		- Negative if the point is in the line's inside half plane
		- Positive if the point is in the line's outside half plane
		- Zero if the point is on the line
		*/

		float StaticPointToStaticLineSegment(Vector2D *P, LineSegment2D *LS)
		{
			Vector2D edge;

			//return (Vector2DDotProduct(&LS->mN, P) - LS->mNdotP0);


			Vector2DSub(&edge, P, &LS->point0_);
			return Vector2DDotProduct(&LS->line_normal_, &edge);
		}


		/*
		This function checks whether an animated point is colliding with a line segment

		- Parameters
		- Ps:		The point's starting location
		- Pe:		The point's ending location
		- LS:		The line segment
		- Pi:		This will be used to store the intersection point's coordinates (In case there's an inte rsection)

		- Returned value: Intersection time t
		- -1.0f:				If there's no intersection
		- Intersection time:	If there's an intersection
		*/
		float AnimatedPointToStaticLineSegment(Vector2D *Ps, Vector2D *Pe, LineSegment2D *LS, Vector2D *Pi)
		{

			float dot_with_ps, dot_with_pe, dot_with_vel;
			Vector2D point_vel, intersection_to_po, po_to_p1;
			float time_of_interesection;


			Vector2DSub(&point_vel, Pe, Ps);
			dot_with_ps = Vector2DDotProduct(Ps, &LS->line_normal_);
			dot_with_pe = Vector2DDotProduct(Pe, &LS->line_normal_);
			dot_with_vel = Vector2DDotProduct(&point_vel, &LS->line_normal_);


			if (dot_with_pe < LS->normal_dot_point0_ && dot_with_ps < LS->normal_dot_point0_) {

				return -1.0f;
			}
			else if (dot_with_pe > LS->normal_dot_point0_ && dot_with_ps > LS->normal_dot_point0_) {

				return -1.0f;
			}
			else if (dot_with_vel == 0) {

				return -1.0f;
			}


			time_of_interesection = (LS->normal_dot_point0_ - dot_with_ps) / dot_with_vel;

			if (time_of_interesection < 0 || time_of_interesection>1) {

				return -1.0f;
			}

			Vector2DScaleAdd(Pi, &point_vel, Ps, time_of_interesection);

			Vector2DSub(&intersection_to_po, Pi, &LS->point0_);
			Vector2DSub(&po_to_p1, &LS->point1_, &LS->point0_);

			if (Vector2DDotProduct(&po_to_p1, &intersection_to_po) < 0) {

				return -1.0f;
			}


			Vector2DSub(&intersection_to_po, Pi, &LS->point1_);
			Vector2DSub(&po_to_p1, &LS->point0_, &LS->point1_);

			if (Vector2DDotProduct(&po_to_p1, &intersection_to_po) < 0) {

				return -1.0f;
			}

			return time_of_interesection;
		}


		/*
		This function checks whether an animated circle is colliding with a line segment

		- Parameters
		- Ps:		The center's starting location
		- Pe:		The center's ending location
		- Radius:	The circle's radius
		- LS:		The line segment
		- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)

		- Returned value: Intersection time t
		- -1.0f:				If there's no intersection
		- Intersection time:	If there's an intersection
		*/
		float AnimatedCircleToStaticLineSegment(Vector2D *Ps, Vector2D *Pe, float Radius, LineSegment2D *LS, Vector2D *Pi)
		{
			float dot_with_ps, dot_with_pe, dot_with_vel;
			Vector2D point_vel, intersection_to_po, po_to_p1;
			float time_of_interesection;


			Vector2DSub(&point_vel, Pe, Ps);
			dot_with_ps = Vector2DDotProduct(Ps, &LS->line_normal_);
			dot_with_pe = Vector2DDotProduct(Pe, &LS->line_normal_);
			dot_with_vel = Vector2DDotProduct(&point_vel, &LS->line_normal_);


			if (dot_with_pe - LS->normal_dot_point0_ < -Radius && dot_with_ps - LS->normal_dot_point0_ < -Radius) {

				return -1.0f;
			}
			else if (dot_with_pe - LS->normal_dot_point0_ > Radius && dot_with_ps - LS->normal_dot_point0_ > Radius) {

				return -1.0f;
			}
			else if (dot_with_vel == 0) {

				return -1.0f;
			}

			if (StaticPointToStaticLineSegment(Ps, LS)<0) {


				Radius *= -1;
			}


			time_of_interesection = (LS->normal_dot_point0_ - dot_with_ps + Radius) / dot_with_vel;

			/*if (time_of_interesection < 0 || time_of_interesection>1) {

			return -1.0f;
			}*/

			Vector2DScaleAdd(Pi, &point_vel, Ps, time_of_interesection);

			Vector2DSub(&intersection_to_po, Pi, &LS->point0_);
			Vector2DSub(&po_to_p1, &LS->point1_, &LS->point0_);

			if (Vector2DDotProduct(&po_to_p1, &intersection_to_po) < 0) {

				return -1.0f;
			}


			Vector2DSub(&intersection_to_po, Pi, &LS->point1_);
			Vector2DSub(&po_to_p1, &LS->point0_, &LS->point1_);

			if (Vector2DDotProduct(&po_to_p1, &intersection_to_po) < 0) {

				return -1.0f;
			}

			return time_of_interesection;
		}


		/*
		This function reflects an animated point on a line segment.
		It should first make sure that the animated point is intersecting with the line

		- Parameters
		- Ps:		The point's starting location
		- Pe:		The point's ending location
		- LS:		The line segment
		- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)
		- R:		Reflected vector R

		- Returned value: Intersection time t
		- -1.0f:				If there's no intersection
		- Intersection time:	If there's an intersection
		*/
		float ReflectAnimatedPointOnStaticLineSegment(Vector2D *Ps, Vector2D *Pe, LineSegment2D *LS, Vector2D *Pi, Vector2D *R)
		{
			float t = AnimatedPointToStaticLineSegment(Ps, Pe, LS, Pi);

			if (t == -1.0f) {

				return t;
			}

			Vector2D pi_to_pe, normal;
			float dot_i_to_n;

			///pr = Pi + i -2(i.n)*n;

			//intersection to end point
			Vector2DSub(&pi_to_pe, Pe, Pi);

			//dot of line segement normal and i-to-e
			dot_i_to_n = Vector2DDotProduct(&pi_to_pe, &LS->line_normal_);

			//s
			Vector2DScale(&normal, &LS->line_normal_, dot_i_to_n * 2);

			//R
			Vector2DSub(R, &pi_to_pe, &normal);

			//Vector2DSub(&pi_to_pe, &pi_to_pe, &normal);
			//Vector2DAdd(Pi)

			return t;

		}


		/*
		This function reflects an animated circle on a line segment.
		It should first make sure that the animated point is intersecting with the line

		- Parameters
		- Ps:		The center's starting location
		- Pe:		The center's ending location
		- Radius:	The circle's radius
		- LS:		The line segment
		- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)
		- R:		Reflected vector R

		- Returned value: Intersection time t
		- -1.0f:				If there's no intersection
		- Intersection time:	If there's an intersection
		*/
		float ReflectAnimatedCircleOnStaticLineSegment(Vector2D *Ps, Vector2D *Pe, float Radius, LineSegment2D *LS, Vector2D *Pi, Vector2D *R)
		{

			float t = AnimatedCircleToStaticLineSegment(Ps, Pe, Radius, LS, Pi);

			if (t == -1.0f) {

				return t;
			}

			if (t > 1 || t < 0) {

				return -1.0f;
			}

			Vector2D pi_to_pe, normal;
			float dot_i_to_n;

			///pr = Pi + i -2(i.n)*n;

			//intersection to end point
			Vector2DSub(&pi_to_pe, Pe, Pi);

			//dot of line segement normal and i-to-e
			dot_i_to_n = Vector2DDotProduct(&pi_to_pe, &LS->line_normal_);

			//s
			Vector2DScale(&normal, &LS->line_normal_, dot_i_to_n * 2);

			//R
			Vector2DSub(R, &pi_to_pe, &normal);

			return t;
		}


		//Part2 Starts here//
		/*
		This function checks whether an animated point is colliding with a static circle

		- Parameters
		- Ps:		The point's starting location
		- Pe:		The point's ending location
		- Center:	The circle's center
		- Radius:	The circle's radius
		- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)

		- Returned value: Intersection time t
		- -1.0f:		If there's no intersection
		- Intersection time:	If there's an intersection
		*/
		float AnimatedPointToStaticCircle(Vector2D *Ps, Vector2D *Pe, Vector2D *Center, float Radius, Vector2D *Pi)
		{

			float t = -1.0f, a, b, c, m, n_squared, s_squared;

			Vector2D ps_c, pv, normal_v;

			Vector2DSub(&ps_c, Center, Ps);
			Vector2DSub(&pv, Pe, Ps);

			// a = v.v
			a = Vector2DDotProduct(&pv, &pv);

			//b = -2(psc).(pv)
			b = -2 * (Vector2DDotProduct(&ps_c, &pv));

			//c = (ps_c . ps_c) - r2

			c = Vector2DDotProduct(&ps_c, &ps_c) - (Radius*Radius);

			//b2-4ac
			float delta = (b*b) - (4 * (a*c));

			//misses circle
			if (delta < 0) {

				return t;
			}


			Vector2DNormalize(&normal_v, &pv);
			m = Vector2DDotProduct(&ps_c, &normal_v);

			n_squared = Vector2DSquareLength(&ps_c) - (m*m);


			if (m < 0) {

				return -1.0f;
			}


			if (n_squared > Radius*Radius) {


				return -1.0f;
			}

			s_squared = (Radius*Radius) - n_squared;


			t = (m - sqrtf(s_squared)) / Vector2DLength(&pv);

			Vector2DScaleAdd(Pi, &pv, Ps, t);
			return t;

			//touches at one point
			/*if ((delta - delta) < EPSILON) {


			t = (-b) / 2 * (a);

			//	if (t > 0.0f && t < 1.0f) {


			Vector2DScaleAdd(Pi, &pv , &Ps , t );
			return t;
			///	}
			//	else {

			//	return -1.0f;
			//	}
			}
			return t;*/


		}



		/*
		This function reflects an animated point on a static circle.
		It should first make sure that the animated point is intersecting with the circle

		- Parameters
		- Ps:		The point's starting location
		- Pe:		The point's ending location
		- Center:	The circle's center
		- Radius:	The circle's radius
		- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)
		- R:		Reflected vector R

		- Returned value: Intersection time t
		- -1.0f:		If there's no intersection
		- Intersection time:	If there's an intersection
		*/
		float ReflectAnimatedPointOnStaticCircle(Vector2D *Ps, Vector2D *Pe, Vector2D *Center, float Radius, Vector2D *Pi, Vector2D *R)
		{
			float t = AnimatedPointToStaticCircle(Ps, Pe, Center, Radius, Pi);

			Vector2D c_pi, normalized_c_pi, ps_pi, scaled_n;
			float m_dot_n;

			if (t + 1.0f < EPSILON) {

				return t;
			}

			if (t > 1 || t < 0) {

				return -1.0f;
			}


			Vector2DSub(&c_pi, Pi, Center);
			Vector2DNormalize(&normalized_c_pi, &c_pi);
			Vector2DSub(&ps_pi, Ps, Pe);

			m_dot_n = 2 * Vector2DDotProduct(&ps_pi, &normalized_c_pi);
			Vector2DScale(&scaled_n, &normalized_c_pi, m_dot_n);

			Vector2DSub(R, &scaled_n, &ps_pi);
			Vector2DNormalize(R, R);
			Vector2DScale(R, R, Vector2DLength(&ps_pi)*(1 - t));
			return t;
		}

		/*
		This function checks whether an animated circle is colliding with a static circle

		- Parameters
		- Center0s:		The starting position of the animated circle's center
		- Center0e:		The ending position of the animated circle's center
		- Radius0:		The animated circle's radius
		- Center1:		The static circle's center
		- Radius1:		The static circle's radius
		- Pi:			This will be used to store the intersection point's coordinates (In case there's an intersection)

		- Returned value: Intersection time t
		- -1.0f:		If there's no intersection
		- Intersection time:	If there's an intersection
		*/
		float AnimatedCircleToStaticCircle(Vector2D *Center0s, Vector2D *Center0e, float Radius0, Vector2D *Center1, float Radius1, Vector2D *Pi)
		{
			return AnimatedPointToStaticCircle(Center0s, Center0e, Center1, Radius0 + Radius1, Pi);
		}


		/*
		This function reflects an animated circle on a static circle.
		It should first make sure that the animated circle is intersecting with the static one

		- Parameters
		- Center0s:		The starting position of the animated circle's center
		- Center0e:		The ending position of the animated circle's center
		- Radius0:		The animated circle's radius
		- Center1:		The static circle's center
		- Radius1:		The static circle's radius
		- Pi:			This will be used to store the intersection point's coordinates (In case there's an intersection)
		- R:			Reflected vector R

		- Returned value: Intersection time t
		- -1.0f:		If there's no intersection
		- Intersection time:	If there's an intersection
		*/
		float ReflectAnimatedCircleOnStaticCircle(Vector2D *Center0s, Vector2D *Center0e, float Radius0, Vector2D *Center1, float Radius1, Vector2D *Pi, Vector2D *R)
		{
			/*Vector2DSet(Center1 , 5,0);
			Vector2DSet(Center0s, 3, -1);
			Vector2DSet(Center0e, 7, -1);

			Radius0 = 0;
			Radius1 = 1;*/


			return ReflectAnimatedPointOnStaticCircle(Center0s, Center0e, Center1, Radius0 + Radius1, Pi, R);

			//return AnimatedCircleToStaticCircle(Vector2D *Center0s, Vector2D *Center0e, float Radius0, Vector2D *Center1, float Radius1, Vector2D *Pi);
		}


	}
}
