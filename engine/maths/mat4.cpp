#include "Mat4.h"
#include "vec3.h"
#include "vec4.h"
#include <string>
#include "math-common.h"


#ifdef TEST_MODE
#include "../enginelogger/enginelogger.h"
#endif


namespace enginecore {

	namespace maths {


		Mat4::Mat4()
		{
			memset(elements, 0, 4 * 4 * sizeof(float));
		}

		Mat4::Mat4(float diagonal)
		{
			memset(elements, 0, 4 * 4 * sizeof(float));
			elements[0 + 0 * 4] = diagonal;
			elements[1 + 1 * 4] = diagonal;
			elements[2 + 2 * 4] = diagonal;
			elements[3 + 3 * 4] = diagonal;
		}

		Mat4::Mat4(float* elements)
		{
			memcpy(this->elements, elements, 4 * 4 * sizeof(float));
		}

		Mat4::Mat4(const Vec4& row0, const Vec4& row1, const Vec4& row2, const Vec4& row3)
		{
			rows[0] = row0;
			rows[1] = row1;
			rows[2] = row2;
			rows[3] = row3;
		}

		Mat4 Mat4::Identity()
		{
			return Mat4(1.0f);
		}

		Mat4& Mat4::Multiply(const Mat4& other)
		{
			float data[16];
			for (int row = 0; row < 4; row++)
			{
				for (int col = 0; col < 4; col++)
				{
					float sum = 0.0f;
					for (int e = 0; e < 4; e++)
					{
						sum += elements[e + row * 4] * other.elements[col + e * 4];
					}
					data[col + row * 4] = sum;
				}
			}
			memcpy(elements, data, 4 * 4 * sizeof(float));
			return *this;
		}

		Vec3 Mat4::Multiply(const Vec3& other) const
		{
			return other.Multiply(*this);
		}

		Vec4 Mat4::Multiply(const Vec4& other) const
		{
			return other.Multiply(*this);
		}

		Mat4 operator*(Mat4 left, const Mat4& right)
		{
			return left.Multiply(right);
		}

		Mat4& Mat4::operator*=(const Mat4& other)
		{
			return Multiply(other);
		}

		Vec3 operator*(const Mat4& left, const Vec3& right)
		{
			return left.Multiply(right);
		}

		Vec4 operator*(const Mat4& left, const Vec4& right)
		{
			return left.Multiply(right);
		}

		Mat4& Mat4::Invert()
		{
			float temp[16];

			temp[0] = elements[5] * elements[10] * elements[15] -
				elements[5] * elements[11] * elements[14] -
				elements[9] * elements[6] * elements[15] +
				elements[9] * elements[7] * elements[14] +
				elements[13] * elements[6] * elements[11] -
				elements[13] * elements[7] * elements[10];

			temp[4] = -elements[4] * elements[10] * elements[15] +
				elements[4] * elements[11] * elements[14] +
				elements[8] * elements[6] * elements[15] -
				elements[8] * elements[7] * elements[14] -
				elements[12] * elements[6] * elements[11] +
				elements[12] * elements[7] * elements[10];

			temp[8] = elements[4] * elements[9] * elements[15] -
				elements[4] * elements[11] * elements[13] -
				elements[8] * elements[5] * elements[15] +
				elements[8] * elements[7] * elements[13] +
				elements[12] * elements[5] * elements[11] -
				elements[12] * elements[7] * elements[9];

			temp[12] = -elements[4] * elements[9] * elements[14] +
				elements[4] * elements[10] * elements[13] +
				elements[8] * elements[5] * elements[14] -
				elements[8] * elements[6] * elements[13] -
				elements[12] * elements[5] * elements[10] +
				elements[12] * elements[6] * elements[9];

			temp[1] = -elements[1] * elements[10] * elements[15] +
				elements[1] * elements[11] * elements[14] +
				elements[9] * elements[2] * elements[15] -
				elements[9] * elements[3] * elements[14] -
				elements[13] * elements[2] * elements[11] +
				elements[13] * elements[3] * elements[10];

			temp[5] = elements[0] * elements[10] * elements[15] -
				elements[0] * elements[11] * elements[14] -
				elements[8] * elements[2] * elements[15] +
				elements[8] * elements[3] * elements[14] +
				elements[12] * elements[2] * elements[11] -
				elements[12] * elements[3] * elements[10];

			temp[9] = -elements[0] * elements[9] * elements[15] +
				elements[0] * elements[11] * elements[13] +
				elements[8] * elements[1] * elements[15] -
				elements[8] * elements[3] * elements[13] -
				elements[12] * elements[1] * elements[11] +
				elements[12] * elements[3] * elements[9];

			temp[13] = elements[0] * elements[9] * elements[14] -
				elements[0] * elements[10] * elements[13] -
				elements[8] * elements[1] * elements[14] +
				elements[8] * elements[2] * elements[13] +
				elements[12] * elements[1] * elements[10] -
				elements[12] * elements[2] * elements[9];

			temp[2] = elements[1] * elements[6] * elements[15] -
				elements[1] * elements[7] * elements[14] -
				elements[5] * elements[2] * elements[15] +
				elements[5] * elements[3] * elements[14] +
				elements[13] * elements[2] * elements[7] -
				elements[13] * elements[3] * elements[6];

			temp[6] = -elements[0] * elements[6] * elements[15] +
				elements[0] * elements[7] * elements[14] +
				elements[4] * elements[2] * elements[15] -
				elements[4] * elements[3] * elements[14] -
				elements[12] * elements[2] * elements[7] +
				elements[12] * elements[3] * elements[6];

			temp[10] = elements[0] * elements[5] * elements[15] -
				elements[0] * elements[7] * elements[13] -
				elements[4] * elements[1] * elements[15] +
				elements[4] * elements[3] * elements[13] +
				elements[12] * elements[1] * elements[7] -
				elements[12] * elements[3] * elements[5];

			temp[14] = -elements[0] * elements[5] * elements[14] +
				elements[0] * elements[6] * elements[13] +
				elements[4] * elements[1] * elements[14] -
				elements[4] * elements[2] * elements[13] -
				elements[12] * elements[1] * elements[6] +
				elements[12] * elements[2] * elements[5];

			temp[3] = -elements[1] * elements[6] * elements[11] +
				elements[1] * elements[7] * elements[10] +
				elements[5] * elements[2] * elements[11] -
				elements[5] * elements[3] * elements[10] -
				elements[9] * elements[2] * elements[7] +
				elements[9] * elements[3] * elements[6];

			temp[7] = elements[0] * elements[6] * elements[11] -
				elements[0] * elements[7] * elements[10] -
				elements[4] * elements[2] * elements[11] +
				elements[4] * elements[3] * elements[10] +
				elements[8] * elements[2] * elements[7] -
				elements[8] * elements[3] * elements[6];

			temp[11] = -elements[0] * elements[5] * elements[11] +
				elements[0] * elements[7] * elements[9] +
				elements[4] * elements[1] * elements[11] -
				elements[4] * elements[3] * elements[9] -
				elements[8] * elements[1] * elements[7] +
				elements[8] * elements[3] * elements[5];

			temp[15] = elements[0] * elements[5] * elements[10] -
				elements[0] * elements[6] * elements[9] -
				elements[4] * elements[1] * elements[10] +
				elements[4] * elements[2] * elements[9] +
				elements[8] * elements[1] * elements[6] -
				elements[8] * elements[2] * elements[5];

			float determinant = elements[0] * temp[0] + elements[1] * temp[4] + elements[2] * temp[8] + elements[3] * temp[12];
			determinant = 1.0f / determinant;

			for (int i = 0; i < 4 * 4; i++)
				elements[i] = temp[i] * determinant;

			return *this;
		}

		Vec4 Mat4::GetColumn(int index)
		{
			return Vec4(elements[index + 0 * 4], elements[index + 1 * 4], elements[index + 2 * 4], elements[index + 3 * 4]);
		}

		void Mat4::SetColumn(int index, const Vec4& column)
		{
			elements[index + 0 * 4] = column.get_x();
			elements[index + 1 * 4] = column.get_y();
			elements[index + 2 * 4] = column.get_z();
			elements[index + 3 * 4] = column.get_w();
		}

		Mat4 Mat4::Orthographic(float left, float right, float bottom, float top, float near, float far)
		{
			Mat4 result(1.0f);

			result.elements[0 + 0 * 4] = 2.0f / (right - left);

			result.elements[1 + 1 * 4] = 2.0f / (top - bottom);

			result.elements[2 + 2 * 4] = 2.0f / (near - far);

			result.elements[3 + 0 * 4] = (left + right) / (left - right);
			result.elements[3 + 1 * 4] = (bottom + top) / (bottom - top);
			result.elements[3 + 2 * 4] = -(far + near) / (far - near);

			return result;
		}

		Mat4 Mat4::Perspective(float fov, float aspectRatio, float near, float far)
		{
			Mat4 result(1.0f);

			float q = 1.0f / tan(ConvertToRadians(0.5f * fov));
			float a = q / aspectRatio;

			float b = (near + far) / (near - far);
			float c = (2.0f * near * far) / (near - far);

			result.elements[0 + 0 * 4] = a;
			result.elements[1 + 1 * 4] = q;
			result.elements[2 + 2 * 4] = b;
			result.elements[2 + 3 * 4] = -1.0f;
			result.elements[3 + 2 * 4] = c;

			/*Mat4 result(1.0f);

			float q = 1.0f / tanf(ConvertToRadians(0.5f * fov));
			float a = q * aspectRatio;

			float b = (near + far) / (near - far);
			float c = (2.0f * near * far) / (near - far);

			result.elements[0 + 0 * 4] = q;
			result.elements[1 + 1 * 4] = a;
			result.elements[2 + 2 * 4] = b;
			result.elements[2 + 3 * 4] = c;
			result.elements[3 + 2 * 4] = -1.0f;*/



			return result;
		}

		Mat4 Mat4::LookAt(const Vec3& camera, const Vec3& object, const Vec3& up)
		{
			Mat4 result = Identity();
			Vec3 f = (object - camera).Normalize();
			Vec3 s = f.Cross(up.Normalize());
			Vec3 u = s.Cross(f);

			result.elements[0 + 0 * 4] = s.get_x();
			result.elements[0 + 1 * 4] = s.get_y();
			result.elements[0 + 2 * 4] = s.get_z();

			result.elements[1 + 0 * 4] = u.get_x();
			result.elements[1 + 1 * 4] = u.get_y();
			result.elements[1 + 2 * 4] = u.get_z();

			result.elements[2 + 0 * 4] = -f.get_x();
			result.elements[2 + 1 * 4] = -f.get_y();
			result.elements[2 + 2 * 4] = -f.get_z();

			return result * Translate(Vec3(-camera.get_x(), -camera.get_y(), -camera.get_z()));
		}

		Mat4 Mat4::Translate(const Vec3& translate)
		{
			Mat4 result(1.0f);

			result.elements[3 + 0 * 4] = translate.get_x();
			result.elements[3 + 1 * 4] = translate.get_y();
			result.elements[3 + 2 * 4] = translate.get_z();

			return result;
		}

		Mat4 Mat4::Rotate(float angle, const Vec3& axis)
		{
			Mat4 result(1.0f);

			float r = ConvertToRadians(angle);
			float c = cos(r);
			float s = sin(r);
			float omc = 1.0f - c;

			float x = axis.get_x();
			float y = axis.get_y();
			float z = axis.get_z();

			result.elements[0 + 0 * 4] = x * x * omc + c;
			result.elements[0 + 1 * 4] = y * x * omc + z * s;
			result.elements[0 + 2 * 4] = x * z * omc - y * s;

			result.elements[1 + 0 * 4] = x * y * omc - z * s;
			result.elements[1 + 1 * 4] = y * y * omc + c;
			result.elements[1 + 2 * 4] = y * z * omc + x * s;

			result.elements[2 + 0 * 4] = x * z * omc + y * s;
			result.elements[2 + 1 * 4] = y * z * omc - x * s;
			result.elements[2 + 2 * 4] = z * z * omc + c;

			return result;
		}

		Mat4 Mat4::Scale(const Vec3& scale)
		{
			Mat4 result(1.0f);

			result.elements[0 + 0 * 4] = scale.get_x();
			result.elements[1 + 1 * 4] = scale.get_y();
			result.elements[2 + 2 * 4] = scale.get_z();

			return result;
		}

		Mat4 Mat4::Invert(const Mat4& matrix)
		{
			Mat4 result = matrix;
			return result.Invert();
		}

		Mat4 Mat4::Transpose(const Mat4& matrix)
		{
			return Mat4(
				Vec4(matrix.rows[0].get_x(), matrix.rows[1].get_x(), matrix.rows[2].get_x(), matrix.rows[3].get_x()),
				Vec4(matrix.rows[0].get_y(), matrix.rows[1].get_y(), matrix.rows[2].get_y(), matrix.rows[3].get_y()),
				Vec4(matrix.rows[0].get_z(), matrix.rows[1].get_z(), matrix.rows[2].get_z(), matrix.rows[3].get_z()),
				Vec4(matrix.rows[0].get_w(), matrix.rows[1].get_w(), matrix.rows[2].get_w(), matrix.rows[3].get_w())
			);
		}

		Mat4 Mat4 ::Modeling(const Vec2& translate, const Vec2& scaling, float rotate) {
			Vec3 t(translate);
			Vec3 s(scaling);
			Vec3 r(0.0f,1.0f,0.0f);


			t.set_z(-3.0f);
		//	return Mat4(Translate(t)*Rotate(rotate, r)*Scale(s));
			return Mat4(Scale(s));
		}

		void Mat4::Print() {


#ifdef TEST_MODE
			for (int i = 0; i < 4; i++) {

				ENGINE_LOG("%.2f %.2f %.2f %.2f", elements[i*4], elements[i * 4 + 1], elements[i * 4 + 2], elements[i * 4 + 3]);
			}
#endif
		
		}
	}
}