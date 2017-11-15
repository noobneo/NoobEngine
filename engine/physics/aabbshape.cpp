#include "aabbshape.h"

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

#ifdef TEST_MODE
			ENGINE_LOG("Destroying the AabbShape");
#endif // TEST_MODE

		}
	}
}
