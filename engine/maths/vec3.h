#ifndef _VEC3_H_
#define _VEC3_H_


namespace enginecore {

	namespace maths {

		class Vec2;
		class Vec4;
		class Mat4;

		class Vec3 {


		private:
			float x_;
			float y_;
			float z_;
		public:
			Vec3();
			Vec3(float scalar);
			Vec3(float x, float y, float z);
			Vec3(const Vec2& other);
			Vec3(float x, float y);
			Vec3(const Vec4& other);

			~Vec3();

			inline void set_x(float x) { x_ = x; };
			inline void set_y(float y) { y_ = y; };
			inline void set_z(float z) { z_ = z; };

			inline float get_x()const { return x_; };
			inline float get_y()const  { return y_; };
			inline float get_z()const  { return z_; };
			
			static Vec3 Up();
			static Vec3 Down();
			static Vec3 Left();
			static Vec3 Right();
			static Vec3 Zero();

			static Vec3 XAxis();
			static Vec3 YAxis();
			static Vec3 ZAxis();

			Vec3 Vec3::Cross(const Vec3& other) const;

			float Length();
			float Length()const;

			float SquareLength()const;
			float SquareLength();

			float Distance(const Vec3& other);
			float SquareDistance(const Vec3& other);

			float DotProduct(const Vec3& other);

			Vec3& SetToZero();
			Vec3& Set(float &x, float &y , float &z);

			Vec3& Negate();

			void  Add(float &x, float &y , float &z);
			Vec3& Add(const Vec3& vec);

			void  Substract(float &x, float &y , float &z);
			Vec3& Substract(const Vec3& vec);

			Vec3& Scale(float &s);


			Vec3& Multiply(const Vec3& vec);
			Vec3 Multiply(const Mat4& transform) const;

			Vec3& GetNormalized();
			Vec3 Normalize()const;

			Vec3& Vec3FromAngleDeg(float angle);
			Vec3& Vec3FromAngleRadian(float radian);

			float AngleFromVec3();
			float AngleFromVec3(const Vec3&);

			Vec3& operator+=(const Vec3& vec1);
			Vec3& operator*=(const Vec3& vec1);
			Vec3& operator-=(const Vec3& vec1);

			friend Vec3 operator- (const Vec3& lhs, const Vec3& rhs);
			friend Vec3 operator+ (const Vec3& lhs, const Vec3& rhs);


		};


	}
}

#endif // !_Vec3_H_
