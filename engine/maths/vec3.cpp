#include "vec3.h"
#include "math-common.h"
#include <math.h>
#include "vec2.h"
#include "vec4.h"
#include "mat4.h"

namespace enginecore {


	namespace maths {

		Vec3::Vec3() :
			x_( 0.0f) , y_ (0.0f) , z_ (0.0f) {
		
		}

		Vec3::Vec3(float scalar)
			: x_(scalar), y_(scalar), z_(scalar){
		}

		Vec3::Vec3(float x, float y, float z)
			: x_(x), y_(y), z_(z){
		}

		Vec3::Vec3(const Vec2& other)
			: x_(other.get_x()), y_(other.get_x()), z_(0.0f)	{
		}

		Vec3::Vec3(float x, float y)
			: x_(x), y_(y), z_(0.0f)	{
		}

		Vec3::Vec3(const Vec4& other)
			: x_(other.get_x()), y_(other.get_y()), z_(other.get_z()){
		}



		Vec3::~Vec3() {

		}


		Vec3 Vec3::Up(){
			return Vec3(0.0f, 1.0f, 0.0f);
		}

		Vec3 Vec3::Down(){
			return Vec3(0.0f, -1.0f, 0.0f);
		}

		Vec3 Vec3::Left(){
			return Vec3(-1.0f, 0.0f, 0.0f);
		}

		Vec3 Vec3::Right(){
			return Vec3(1.0f, 1.0f, 0.0f);
		}

		Vec3 Vec3::Zero(){
			return Vec3(0.0f, 0.0f, 0.0f);
		}

		Vec3 Vec3::XAxis(){
			return Vec3(1.0f, 0.0f, 0.0f);
		}

		Vec3 Vec3::YAxis()	{
			return Vec3(0.0f, 1.0f, 0.0f);
		}

		Vec3 Vec3::ZAxis()	{
			return Vec3(0.0f, 0.0f, 1.0f);
		}




		Vec3 Vec3::Cross(const Vec3& other) const
		{
			return Vec3(y_ * other.get_z() - z_ * other.get_y(), z_ * other.get_x() - x_ * other.get_z(), x_ * other.get_y() - y_ * other.get_x());
		}



		float Vec3::Length() {

			return sqrtf(SquareLength());
		}


		float  Vec3::Length()const {

			return sqrtf(SquareLength());
		}


		float Vec3::SquareLength()const {

			return (x_*x_ + y_*y_ + z_*z_);
		}


		float Vec3::SquareLength() {

			return (x_*x_ + y_*y_ + z_*z_);
		}

		float Vec3::Distance(const Vec3& other) {

			return sqrtf(SquareDistance(other));
		}


		float Vec3::SquareDistance(const Vec3& other) {

			/*
			* d = sqrt((x2-x1)^2 + (y2-y1)^2)
			* d^2 = (x2-x1)^2 + (y2-y1)^2
			*/
			return (((x_ - other.x_)*(x_ - other.y_)) + ((y_ - other.y_)*(y_ - other.y_)) + ((z_ - other.z_)*(z_ - other.z_)));
		}

		float Vec3::DotProduct(const Vec3& other) {

			return x_*other.x_ + y_*other.y_ + z_*other.z_;
		}

		Vec3& Vec3::SetToZero() {

			x_ = 0.0f;
			y_ = 0.0f;
			z_ = 0.0f;

			return *this;
		}

		Vec3& Vec3::Set(float &x, float &y , float& z) {

			x_ = x;
			y_ = y;
			z_ = z;
			return *this;
		}

		Vec3& Vec3::Negate() {

			x_ *= -1;
			y_ *= -1;
			z_ *= -1;

			return *this;
		}


		void Vec3::Add(float &x, float &y , float &z) {

			x_ += x;
			y_ += y;
			z_ += z;
		}

		Vec3& Vec3::Add(const Vec3& vec) {

			x_ += vec.x_;
			y_ += vec.y_;
			z_ += vec.z_;

			return *this;
		}

		void Vec3::Substract(float &x, float &y , float &z) {

			x_ -= x;
			y_ -= y;
			z_ -= z;
		}

		Vec3& Vec3::Substract(const Vec3& vec) {

			x_ -= vec.x_;
			y_ -= vec.y_;
			z_ -= vec.z_;

			return *this;
		}


		Vec3& Vec3::Scale(float &s) {

			x_ *= s;
			y_ *= s;
			z_ *= s;

			return *this;
		}


		Vec3& Vec3::Multiply(const Vec3& vec) {

			x_ *= vec.x_;
			y_ *= vec.y_;
			z_ *= vec.z_;

			return *this;
		}

		Vec3 Vec3::Multiply(const Mat4& transform) const
		{
			return Vec3(
				transform.rows[0].get_x() * x_ + transform.rows[0].get_y() * y_ + transform.rows[0].get_z() * z_ + transform.rows[0].get_w(),
				transform.rows[1].get_x() * x_ + transform.rows[1].get_y() * y_ + transform.rows[1].get_z() * z_ + transform.rows[1].get_w(),
				transform.rows[2].get_x() * x_ + transform.rows[2].get_y() * y_ + transform.rows[2].get_z() * z_ + transform.rows[2].get_w()
			);
		}




		Vec3& Vec3::GetNormalized() {


			float len = Length();

			if (len) {
				x_ = (x_) / len;
				y_ = (y_) / len;
				z_ = (z_) / len;
			}
			return *this;
		}

		Vec3 Vec3::Normalize()const {

			float len = 1.0f/Length();

			return Vec3((x_) * len, (y_)* len, (z_) * len);//check again
		}

		Vec3& Vec3::Vec3FromAngleDeg(float angle) {

			angle = (float)(angle * MATH_PI / 180.0f);

			return Vec3FromAngleRadian(angle);
		}

		Vec3& Vec3::Vec3FromAngleRadian(float radian) {

			x_ = (float)(1.0f * cosf(radian));
			y_ = (float)(1.0f * sinf(radian));

			return *this;
		}


		float Vec3::AngleFromVec3() {

			return atan2f(y_, x_);
		}

		float Vec3::AngleFromVec3(const Vec3& vec) {

			float dx = y_ * vec.z_ - z_ * vec.y_;
			float dy = z_ * vec.x_ - x_ * vec.z_;
			float dz = x_ * vec.y_ - y_ * vec.x_;

			return atan2f(sqrtf(dx * dx + dy * dy + dz * dz) + MATH_FLOAT_SMALL, DotProduct(vec));
		}

		Vec3& Vec3::operator+=(const Vec3& vec1) {

			return Add(vec1);
		}

		Vec3& Vec3::operator*=(const Vec3& vec1) {

			return Multiply(vec1);
		}

		Vec3& Vec3::operator-=(const Vec3& vec1) {

			return Substract(vec1);
		}

		Vec3 operator- (const Vec3& lhs, const Vec3& rhs) {

			return Vec3(lhs.x_ - rhs.x_, lhs.y_ - rhs.y_, lhs.z_ - rhs.z_);
		}

		Vec3 operator+ (const Vec3& lhs, const Vec3& rhs) {

			return Vec3(lhs.x_ + rhs.x_, lhs.y_ + rhs.y_, lhs.z_ + rhs.z_);
		}


	}
}