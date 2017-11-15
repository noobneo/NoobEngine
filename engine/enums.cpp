#include "enums.h"
#include "utils\textconverter.h"

namespace enginecore {

	namespace physics {

		BodyType get_body_type(std::string name) {

			BodyType type;
			if (strcmp(utils::TextConverter::GetInstance()->GetLowerCaseFromString(name).c_str(), "static") == 0) {


				type =  E_BODY_TYPE_STATIC;

			}else if (strcmp(utils::TextConverter::GetInstance()->GetLowerCaseFromString(name).c_str(), "kinematic") == 0) {

				type =  E_BODY_TYPE_KINEMATIC;

			} else {

				type =  E_BODY_TYPE_DYNAMIC;
			}

			return type;
		}

		ShapeType get_shape_type(std::string name) {

			ShapeType type;
			if (strcmp(utils::TextConverter::GetInstance()->GetLowerCaseFromString(name).c_str(), "circle") == 0) {


				type = E_SHAPE_CIRCLE;

			}else {

				type = E_SHAPE_AABB;
			}

			return type;
		}
	}
}