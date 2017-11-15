#ifndef _ENUMS_H_
#define _ENUMS_H_

#include <string>

namespace enginecore {

	namespace component {

		typedef enum {

			E_COMPONENT_TYPE_NONE = 0,
			E_COMPONENT_TYPE_BODY,
			E_COMPONENT_TYPE_SHAPE,
			E_COMPONENT_TYPE_RENDER,
			E_COMPONENT_TYPE_BUTTONS,
			E_COMPONENT_TYPE_TRANSFORM,
			E_COMPONENT_TYPE_DEBUG_DRAW,
			E_COMPONENT_TYPE_INPUT_HANDLER,
			E_COMPONENT_TYPE_ANIMATION
		}ComponentType;

	}
}

namespace enginecore {

	namespace physics {

		typedef enum {

			E_BODY_TYPE_STATIC = 1,
			E_BODY_TYPE_DYNAMIC,
			E_BODY_TYPE_KINEMATIC,

		}BodyType;


		typedef enum {

			E_SHAPE_CIRCLE,
			E_SHAPE_AABB,
			E_TOTAL_SHAPES
		}ShapeType;


		BodyType get_body_type(std::string name);
		ShapeType get_shape_type(std::string name);
	}
}




#endif // !_ENUMS_H_
