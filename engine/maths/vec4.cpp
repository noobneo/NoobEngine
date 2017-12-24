#include "Vec4.h"
#include "math-common.h"
#include <math.h>
#include "vec3.h"
#include "mat4.h"

namespace enginecore {


	namespace maths {

		Vec4::Vec4() :
			x_(0.0f), y_(0.0f), z_(0.0f), w_(0.0f) {

		}

		Vec4::Vec4(float scalar)
			: x_(scalar), y_(scalar), z_(scalar), w_(scalar)
		{
		}

		Vec4::Vec4(float x, float y, float z, float w)
			: x_(x), y_(y), z_(z), w_(w)
		{
		}

		Vec4::Vec4(const Vec3& vec, float w)
			: x_(vec.get_x()), y_(vec.get_y()), z_(vec.get_z()), w_(w)
		{
		}



		Vec4::~Vec4() {


		}


		float Vec4::Length() {

			return sqrtf(SquareLength());
		}


		float Vec4::SquareLength() {

			return (x_*x_ + y_*y_ + z_*z_ + w_*w_);
		}

		float Vec4::Distance(const Vec4& other) {

			return sqrtf(SquareDistance(other));
		}


		float Vec4::SquareDistance(const Vec4& other) {

			/*
			* d = sqrt((x2-x1)^2 + (y2-y1)^2)
			* d^2 = (x2-x1)^2 + (y2-y1)^2
			*/
			return (((x_ - other.x_)*(x_ - other.y_)) + ((y_ - other.y_)*(y_ - other.y_)) + ((z_ - other.z_)*(z_ - other.z_)) + +((w_ - other.w_)*(w_ - other.w_)));
		}

		float Vec4::DotProduct(const Vec4& other) {

			return x_*other.x_ + y_*other.y_ + z_*other.z_ + w_*other.w_;
		}

		Vec4& Vec4::SetToZero() {

			x_ = 0.0f;
			y_ = 0.0f;
			z_ = 0.0f;
			w_ = 0.0f;

			return *this;
		}

		Vec4& Vec4::Set(float &x, float &y, float& z , float &w) {

			x_ = x;
			y_ = y;
			z_ = z;
			w_ = w;

			return *this;
		}

		Vec4& Vec4::Negate() {

			x_ *= -1;
			y_ *= -1;
			z_ *= -1;
			w_ *= -1;

			return *this;
		}


		void Vec4::Add(float &x, float &y, float &z, float &w) {

			x_ += x;
			y_ += y;
			z_ += z;
			w_ += w_;
		}

		Vec4& Vec4::Add(const Vec4& vec) {

			x_ += vec.x_;
			y_ += vec.y_;
			z_ += vec.z_;
			w_ += vec.w_;

			return *this;
		}

		void Vec4::Substract(float &x, float &y, float &z, float &w) {

			x_ -= x;
			y_ -= y;
			z_ -= z;
			w_ -= w_;
		}

		Vec4& Vec4::Substract(const Vec4& vec) {

			x_ -= vec.x_;
			y_ -= vec.y_;
			z_ -= vec.z_;
			w_ -= vec.w_;

			return *this;
		}


		Vec4& Vec4::Scale(float &s) {

			x_ *= s;
			y_ *= s;
			z_ *= s;
			w_ *= s;

			return *this;
		}


		Vec4& Vec4::Multiply(const Vec4& vec) {

			x_ *= vec.x_;
			y_ *= vec.y_;
			z_ *= vec.z_;
			w_ *= vec.w_;

			return *this;
		}


		Vec4 Vec4::Multiply(const Mat4& transform) const
		{
			return Vec4(
				transform.rows[0].get_x() * x_ + transform.rows[0].get_y() * y_ + transform.rows[0].get_z() * z_ + transform.rows[0].get_w()*w_,
				transform.rows[1].get_x() * x_ + transform.rows[1].get_y() * y_ + transform.rows[1].get_z() * z_ + transform.rows[1].get_w()*w_,
				transform.rows[2].get_x() * x_ + transform.rows[2].get_y() * y_ + transform.rows[2].get_z() * z_ + transform.rows[2].get_w()*w_,
				transform.rows[2].get_x() * x_ + transform.rows[2].get_y() * y_ + transform.rows[2].get_z() * z_ + transform.rows[2].get_w()*w_
			);
		}



		Vec4& Vec4::Normalize() {


			float len = Length();

			if (len) {
				x_ = (x_) / len;
				y_ = (y_) / len;
				z_ = (z_) / len;
				w_ = (w_) / len;
			}
			return *this;
		}

		float Vec4::AngleFromVec4(const Vec4& vec) {

			float dx = w_ * vec.x_ - x_ * vec.w_ - y_ * vec.z_ + z_ * vec.y_;
			float dy = w_ * vec.y_ - y_ * vec.w_ - z_ * vec.x_ + x_ * vec.z_;
			float dz = w_ * vec.z_ - z_ * vec.w_ - x_ * vec.y_ + y_ * vec.x_;

			return atan2f(sqrtf((dx * dx + dy * dy + dz * dz)) + MATH_FLOAT_SMALL, DotProduct(vec));
		}

		Vec4& Vec4::operator+=(const Vec4& vec1) {

			return Add(vec1);
		}

		Vec4& Vec4::operator*=(const Vec4& vec1) {

			return Multiply(vec1);
		}

		Vec4& Vec4::operator-=(const Vec4& vec1) {

			return Substract(vec1);
		}
	}
}