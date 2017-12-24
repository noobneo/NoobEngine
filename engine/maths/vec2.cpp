#include "vec2.h"
#include "math-common.h"
#include <math.h>

namespace enginecore {


	namespace maths {

			Vec2::Vec2() :
				x_(0.0f), y_(0.0f) {

			}

			Vec2::Vec2(float x , float y) :
				x_(x), y_(y) {

			}


			Vec2::~Vec2() {


			}


			float Vec2::Length() {

				return sqrtf(SquareLength());
			}


			float Vec2::SquareLength() {

				return (x_*x_ + y_*y_);
			}

			float Vec2::Length()const {

				return sqrtf(SquareLength());
			}

			float Vec2::SquareLength()const {

				return (x_*x_ + y_*y_);

			}



			float Vec2::Distance(const Vec2& other) {

				return sqrtf(SquareDistance(other));
			}


			float Vec2::SquareDistance(const Vec2& other) {

				/*
				* d = sqrt((x2-x1)^2 + (y2-y1)^2)
				* d^2 = (x2-x1)^2 + (y2-y1)^2
				*/
				return (((x_ - other.x_)*(x_ - other.y_)) + ((y_ - other.y_)*(y_ - other.y_)));
			}

			float Vec2::DotProduct(const Vec2& other) {
			
				return x_*other.x_ + y_*other.y_;
			}

			Vec2& Vec2::SetToZero() {
			
				x_ = 0.0f;
				y_ = 0.0f;

				return *this;
			}

			Vec2& Vec2::Set(float x, float y) {
			
				x_ = x;
				y_ = y;

				return *this;
			}

			Vec2& Vec2::Negate() {
			
				x_ *=-1 ;
				y_ *=-1;

				return *this;
			}


			void Vec2::Add(float &x, float &y) {
			
				x_ += x;
				y_ += y;
			}

			Vec2& Vec2::Add(const Vec2& vec) {
			
				x_ += vec.x_;
				y_ += vec.y_;

				return *this;
			}

			void Vec2::Substract(float &x, float &y) {

				x_ -= x;
				y_ -= y;
			}

			Vec2& Vec2::Substract(const Vec2& vec) {
			
				x_ -= vec.x_;
				y_ -= vec.y_;

				return *this;
			}


			Vec2& Vec2::Scale(float &s) {
			
				x_ *= s;
				y_ *= s;

				return *this;
			}

	
			Vec2& Vec2::Multiply(const Vec2& vec) {
			
				x_ *= vec.x_;
				y_ *= vec.y_;

				return *this;
			}


			Vec2& Vec2::GetNormalized() {
			

				float len = Length();

				if (len) {
					x_ = (x_) / len;
					y_ = (y_) / len;
				}
				return *this;
			}

			Vec2 Vec2::Normalize()const {

				float len = Length();

				return Vec2(x_ / len, y_ / len);
			}



			Vec2& Vec2::Vec2FromAngleDeg(float angle) {
			
				angle = (float)(angle * MATH_PI / 180.0f);

				return Vec2FromAngleRadian(angle);
			}

			Vec2& Vec2::Vec2FromAngleRadian(float radian) {
			
				x_ = (float)(1.0f * cosf(radian));
				y_ = (float)(1.0f * sinf(radian));

				return *this;
			}


			float Vec2::AngleFromVec2() {
			
				return atan2f(y_, x_);
			}

			float Vec2::AngleFromVec2(const Vec2& vec) {

				float dz = x_ * vec.y_ - y_ * vec.x_;
				return atan2f(fabsf(dz) + MATH_FLOAT_SMALL, DotProduct(vec));
			}

			Vec2& Vec2::operator+=(const Vec2& vec1) {
			
				return Add(vec1);
			}

			Vec2& Vec2::operator*=(const Vec2& vec1) {
			
				return Multiply(vec1);
			}

			Vec2& Vec2::operator-=(const Vec2& vec1) {
			
				return Substract(vec1);
			}


			Vec2 operator- (const Vec2& lhs, const Vec2& rhs) {

				return Vec2(lhs.x_ - rhs.x_, lhs.y_ - rhs.y_);
			}

			Vec2 operator+ (const Vec2& lhs, const Vec2& rhs) {

				return Vec2(lhs.x_ + rhs.x_, lhs.y_ + rhs.y_);
			}
	}
}