#include "shape.h"

#ifdef TEST_MODE
#include "../enginelogger/enginelogger.h"
#endif // TEST_MODE



namespace enginecore {

	namespace physics {

		Shape::~Shape(){


#ifdef TEST_MODE
			ENGINE_LOG("Destroying the shape");
#endif // TEST_MODE


		}
	}
}

