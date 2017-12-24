#include "aabbshape.h"

/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: aabbshape.cpp
Purpose: shape for collision
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 16th October 2017
---------------------------------------------------------*/



#ifdef TEST_MODE
#include "../enginelogger/enginelogger.h"
#endif // TEST_MODE



namespace enginecore {

	namespace physics {

		AabbShape::AabbShape(ShapeType type) : Shape(type) {

			width_	 =	0.0f;
			height_  =	0.0f;
		}

		void AabbShape::set_dimensions(float width, float height) {

			width_ = width;
			height_ = height;
		}

		void AabbShape::Reset() {

			width_ = 0.0f;
			height_ = 0.0f;
		}

		AabbShape::~AabbShape()	{

#ifdef DESTRUCTOR_LOG_MODE
			ENGINE_LOG("Destroying the AabbShape");
#endif // TEST_MODE

		}
	}
}
