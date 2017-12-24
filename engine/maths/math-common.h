#ifndef _COMMON_MATH_H_
#define _COMMON_MATH_H_



#define MATH_PI      3.1415926535897932384626433832795f
#define EPSILON 0.0001f
#define MATH_FLOAT_SMALL            1.0e-37f
#include <math.h>

namespace enginecore {


	namespace maths {


		inline float ConvertToRadians(float degrees)
		{
			return (float)(degrees * (MATH_PI / 180.0f));
		}

		inline float ConvertToDegrees(float radians)
		{
			return (float)(radians * (180.0f / MATH_PI));
		}


		inline float GetAngle(float x, float y) {

			return atan2f(y, x);
		}

	}
}
#endif // !_COMMON_MATH_H_

