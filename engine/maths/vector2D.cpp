/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Vector2D.c
Purpose: Vector2D class which includes implementation of Vector operations
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 ,x86  .Windows
Project: CS529_ajaytanwar_2
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: September 13th 2017
---------------------------------------------------------*/


#include "vector2D.h"
#include "matrix2D.h"
#include <math.h>

namespace enginecore {

	namespace math {

		// ---------------------------------------------------------------------------

		void Vector2DZero(Vector2D *pResult)
		{
			pResult->x_ = 0.0f;
			pResult->y_ = 0.0f;
		}

		// ---------------------------------------------------------------------------

		void Vector2DSet(Vector2D *pResult, float x, float y)
		{
			pResult->x_ = x;
			pResult->y_ = y;
		}

		// ---------------------------------------------------------------------------

		void Vector2DNeg(Vector2D *pResult, Vector2D *pVec0)
		{
			pResult->x_ = -pVec0->x_;
			pResult->y_ = -pVec0->y_;
		}

		// ---------------------------------------------------------------------------

		void Vector2DAdd(Vector2D *pResult, Vector2D *pVec0, Vector2D *pVec1)
		{
			pResult->x_ = pVec0->x_ + pVec1->x_;
			pResult->y_ = pVec0->y_ + pVec1->y_;
		}

		// ---------------------------------------------------------------------------

		void Vector2DSub(Vector2D *pResult, Vector2D *pVec0, Vector2D *pVec1)
		{
			pResult->x_ = pVec0->x_ - pVec1->x_;
			pResult->y_ = pVec0->y_ - pVec1->y_;
		}

		// ---------------------------------------------------------------------------

		void Vector2DNormalize(Vector2D *pResult, Vector2D *pVec0)
		{
			/*
			* todo : change later
			*/
			/*
			Quake3 magic fix for invrs sqrt
			*/
			/*float invrs_sqrt = InverseSquareRoot(Vector2DSquareLength(pVec0));*/

			float len = Vector2DLength(pVec0);

			if (len) {
				pResult->x_ = (pVec0->x_) / len;
				pResult->y_ = (pVec0->y_) / len;
			}
		}

		// ---------------------------------------------------------------------------

		void Vector2DScale(Vector2D *pResult, Vector2D *pVec0, float c)
		{
			pResult->x_ = pVec0->x_ * c;
			pResult->y_ = pVec0->y_ * c;
		}

		// ---------------------------------------------------------------------------

		void Vector2DScaleAdd(Vector2D *pResult, Vector2D *pVec0, Vector2D *pVec1, float c)
		{
			pResult->x_ = pVec0->x_*c + pVec1->x_;
			pResult->y_ = pVec0->y_*c + pVec1->y_;
		}

		// ---------------------------------------------------------------------------

		void Vector2DScaleSub(Vector2D *pResult, Vector2D *pVec0, Vector2D *pVec1, float c)
		{
			pResult->x_ = pVec0->x_*c - pVec1->x_;
			pResult->y_ = pVec0->y_*c - pVec1->y_;
		}

		// ---------------------------------------------------------------------------

		float Vector2DLength(Vector2D *pVec0)
		{
			return sqrtf(Vector2DSquareLength(pVec0));
		}

		// ---------------------------------------------------------------------------

		float Vector2DSquareLength(Vector2D *pVec0)
		{
			/*
			* len = sqrt((x)^2 + (y)^2)
			* len^2 = (x)^2 + (y)^2
			*/
			return pVec0->x_*pVec0->x_ + pVec0->y_*pVec0->y_;
		}

		// ---------------------------------------------------------------------------

		float Vector2DDistance(Vector2D *pVec0, Vector2D *pVec1)
		{
			return sqrtf(Vector2DSquareDistance(pVec0, pVec1));
		}

		// ---------------------------------------------------------------------------

		float Vector2DSquareDistance(Vector2D *pVec0, Vector2D *pVec1)
		{
			/*
			* d = sqrt((x2-x1)^2 + (y2-y1)^2)
			* d^2 = (x2-x1)^2 + (y2-y1)^2
			*/
			return (((pVec0->x_ - pVec1->x_)*(pVec0->x_ - pVec1->x_)) + ((pVec0->y_ - pVec1->y_)*(pVec0->y_ - pVec1->y_)));
		}

		// ---------------------------------------------------------------------------

		float Vector2DDotProduct(Vector2D *pVec0, Vector2D *pVec1)
		{
			return pVec0->x_*pVec1->x_ + pVec0->y_*pVec1->y_;
		}

		// ---------------------------------------------------------------------------

		void Vector2DFromAngleDeg(Vector2D *pResult, float angle)
		{
			/*
			if (angle >= 360.0f) {

			angle = (float )(360.0f - angle);
			}
			*/
			angle = (float)(angle * MATH_PI / 180.0f);// DEG_TO_RAD(angle);

			Vector2DFromAngleRad(pResult, angle);
		}

		// ---------------------------------------------------------------------------

		void Vector2DFromAngleRad(Vector2D *pResult, float angle)
		{
			pResult->x_ = (float)(1.0f * cosf(angle));
			pResult->y_ = (float)(1.0f * sinf(angle));
		}


		void Vector2DFromAngle(Vector2D *pResult, float angle)
		{

			Vector2DFromAngleRad(pResult, angle);
			//pResult->x_ = (float)(1.0f * cosf(angle));
			//pResult->y_ = (float)(1.0f * sinf(angle));
		}

		float Vector2DAngleFromVec2(Vector2D *pResult) {

			return atan2f(pResult->y_, pResult->x_);
		}

		// ---------------------------------------------------------------------------


		/*
		*	Quake 3 Inverse Square Root
		*/

		float InverseSquareRoot(float length) {

			long i;
			float x2, y;
			const float threehalfs = 1.5F;

			x2 = length * 0.5F;
			y = length;
			i = *(long *)&y;
			i = 0x5f3759df - (i >> 1);             //magic number   
			y = *(float *)&i;
			y = y * (threehalfs - (x2 * y * y));   // 1st iteration

			return y;
		}

	}
}
