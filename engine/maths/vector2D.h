#ifndef _VECTOR2_H_
#define _VECTOR2_H_

#define MATH_PI      3.1415926535897932384626433832795
#define EPSILON 0.0001f


namespace enginecore {

	namespace math {

		typedef struct Vector2D
		{

			float x_;
			float y_;

			Vector2D& operator=(const Vector2D& copy) {

				x_ = copy.x_;
				y_ = copy.y_;
				return *this;
			}
		}Vector2D;

		
		void Vector2DZero(Vector2D *pResult);

		void Vector2DSet(Vector2D *pResult, float x, float y);

		void Vector2DNeg(Vector2D *pResult, Vector2D *pVec0);

		void Vector2DAdd(Vector2D *pResult, Vector2D *pVec0, Vector2D *pVec1);

		void Vector2DSub(Vector2D *pResult, Vector2D *pVec0, Vector2D *pVec1);

		void Vector2DNormalize(Vector2D *pResult, Vector2D *pVec0);

		void Vector2DScale(Vector2D *pResult, Vector2D *pVec0, float c);

		void Vector2DScaleAdd(Vector2D *pResult, Vector2D *pVec0, Vector2D *pVec1, float c);

		void Vector2DScaleSub(Vector2D *pResult, Vector2D *pVec0, Vector2D *pVec1, float c);

		float Vector2DLength(Vector2D *pVec0);

		float Vector2DSquareLength(Vector2D *pVec0);

		float Vector2DDistance(Vector2D *pVec0, Vector2D *pVec1);

		float Vector2DSquareDistance(Vector2D *pVec0, Vector2D *pVec1);

		float Vector2DDotProduct(Vector2D *pVec0, Vector2D *pVec1);

		void Vector2DFromAngle(Vector2D *pResult, float angle);

		//takes vector and returns angle
		float Vector2DAngleFromVec2(Vector2D *pResult);

		/*
		This function computes the coordinates of the vector represented by the angle "angle", which is in Degrees
		*/
		void Vector2DFromAngleDeg(Vector2D *pResult, float angle);

		/*
		This function computes the coordinates of the vector represented by the angle "angle", which is in Radian
		*/
		void Vector2DFromAngleRad(Vector2D *pResult, float angle);

		float InverseSquareRoot(float length);
		
	}
}


#endif //_VECTOR2_H_
