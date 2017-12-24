#ifndef _AABB_SHAPE_H_
#define _AABB_SHAPE_H_

/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: aabbshape.h
Purpose: shape for collision
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 16th October 2017
---------------------------------------------------------*/



#include "shape.h"

namespace enginecore {

	namespace physics {

		class AabbShape : public Shape
		{
		public:
			AabbShape() :width_(0.0f), height_(0.0f) {}
			AabbShape(ShapeType type);
			~AabbShape();

			virtual void set_dimensions(float width, float height);
			inline float get_width() { return width_; };
			inline float get_height() { return height_; };
			
			virtual void Reset();
		private:

			float width_;
			float height_;
			
		};

	}
}

#endif // !_AABB_SHAPE_H_
