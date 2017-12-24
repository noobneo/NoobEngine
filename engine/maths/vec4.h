#ifndef _VEC4_H_
#define _VEC4_H_


namespace enginecore {

	namespace maths {

		class Vec3;
		class Mat4;


		class Vec4 {


		private:
			float x_;
			float y_;
			float z_;
			float w_;
		public:
			Vec4();
			Vec4(float scalar);
			Vec4(float x, float y, float z, float w);
			Vec4(const Vec3& xyz, float w);


			~Vec4();



			inline float get_x()const { return x_; };
			inline float get_y()const { return y_; };
			inline float get_z()const { return z_; };
			inline float get_w()const { return w_; };


			float Length();
			float SquareLength();

			float Distance(const Vec4& other);
			float SquareDistance(const Vec4& other);

			float DotProduct(const Vec4& other);

			Vec4& SetToZero();
			Vec4& Set(float &x, float &y, float &z, float &w);

			Vec4& Negate();

			void  Add(float &x, float &y, float &z , float &w);
			Vec4& Add(const Vec4& vec);

			void  Substract(float &x, float &y, float &z , float &w);
			Vec4& Substract(const Vec4& vec);

			Vec4& Scale(float &s);


			Vec4& Multiply(const Vec4& vec);
			Vec4 Multiply(const Mat4& transform) const;

			Vec4& Normalize();


			float AngleFromVec4(const Vec4&);

			Vec4& operator+=(const Vec4& vec1);
			Vec4& operator*=(const Vec4& vec1);
			Vec4& operator-=(const Vec4& vec1);

		};


	}
}

#endif // !_Vec4_H_
