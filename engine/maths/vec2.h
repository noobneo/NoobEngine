#ifndef _VEC2_H_
#define _VEC2_H_


namespace enginecore {
		
	namespace maths {

		class Vec2 {


		private:
			float x_;
			float y_;
		public:
			Vec2();
			Vec2(float x, float y);
			~Vec2();



			inline void set_x(float x) { x_ = x; };
			inline void set_y(float y) { y_ = y; };


			inline float get_x()const  { return x_; };
			inline float get_y()const { return y_; };
			
			float Length();
			float SquareLength();

			float Length()const;
			float SquareLength()const;

			float Distance(const Vec2& other);
			float SquareDistance(const Vec2& other);

			float DotProduct(const Vec2& other);

			Vec2& SetToZero();
			Vec2& Set(float x, float y);

			Vec2& Negate();

			void  Add(float &x, float &y);
			Vec2& Add(const Vec2& vec);

			void  Substract(float &x, float &y);
			Vec2& Substract(const Vec2& vec);

			Vec2& Scale(float &s);


			Vec2& Multiply(const Vec2& vec);

			Vec2& GetNormalized();
			Vec2 Normalize()const;

			Vec2& Vec2FromAngleDeg(float angle);
			Vec2& Vec2FromAngleRadian(float radian);

			float AngleFromVec2();
			float AngleFromVec2(const Vec2&);

			Vec2& operator+=(const Vec2& vec1);
			Vec2& operator*=(const Vec2& vec1);
			Vec2& operator-=(const Vec2& vec1);

			friend Vec2 operator- (const Vec2& lhs, const Vec2& rhs);
			friend Vec2 operator+ (const Vec2& lhs, const Vec2& rhs);

		};


	}
}

#endif // !_VEC2_H_
