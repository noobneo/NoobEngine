#ifndef _Mat4_H_
#define _Mat4_H_

#include "vec3.h"
#include "vec4.h"

namespace enginecore {

	namespace maths {

	
		class Vec4;
		class Vec3;

		class Mat4
		{
			public:

				float elements[4 * 4];
				Vec4 rows[4];

				Mat4();
				Mat4(float diagonal);
				Mat4(float* elements);
				Mat4(const Vec4& row0, const Vec4& row1, const Vec4& row2, const Vec4& row3);

				static Mat4 Identity();

				Mat4& Multiply(const Mat4& other);
				friend Mat4 operator*(Mat4 left, const Mat4& right);
				Mat4& operator*=(const Mat4& other);

				Vec3 Multiply(const Vec3& other) const;
				friend  Vec3 operator*(const Mat4& left, const Vec3& right);

				Vec4 Multiply(const Vec4& other) const;
				friend Vec4 operator*(const Mat4& left, const Vec4& right);

				Mat4& Invert();

				Vec4 GetColumn(int index);
				void SetColumn(int index, const Vec4& column);
				inline Vec3 GetPosition()  { return Vec3(GetColumn(3)); }
				inline void SetPosition(const Vec3& position) { SetColumn(3, Vec4(position, 1.0f)); }

				static Mat4 Orthographic(float left, float right, float bottom, float top, float near, float far);
				static Mat4 Perspective(float fov, float aspectRatio, float near, float far);
				static Mat4 LookAt(const Vec3& camera, const Vec3& object, const Vec3& up);

				static Mat4 Translate(const Vec3& translate);
				static Mat4 Rotate(float angle, const Vec3& axis);
				static Mat4 Scale(const Vec3& scale);
				static Mat4 Invert(const Mat4& matrix);
				static Mat4 Modeling(const Vec2& translate , const Vec2& scaling , float rotate);

				static Mat4 Transpose(const Mat4& matrix);

				inline Vec4* get_rows() { return rows; };

				void Print();

		};

	}
}

#endif // !_Mat4_H_