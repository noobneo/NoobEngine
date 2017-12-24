#include "circleshape.h"

#ifdef TEST_MODE
#include "../enginelogger/enginelogger.h"
#endif // TEST_MODE




namespace enginecore {

	namespace physics {

		CircleShape::CircleShape(ShapeType type) : Shape(type) {

			radius_ = 0.0f;
		}

		void CircleShape::Reset() {

			radius_ = 0.0f;
		}



		CircleShape::~CircleShape() {

#ifdef DESTRUCTOR_LOG_MODE
			ENGINE_LOG("Destroying the CircleShape");
#endif // TEST_MODE

		}
	}
}
