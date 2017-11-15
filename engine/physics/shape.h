#ifndef _SHAPE_H_
#define _SHAPE_H_

#include <string>
#include "../enums.h"

namespace enginecore {

	namespace physics {


	/*	ShapeType get_shape_type(std::string name) {

			if (strcmp(utils::TextConverter::GetInstance()->GetLowerCaseFromString(name).c_str(), "circle") == 0) {

				return E_SHAPE_CIRCLE;
			}
			else {

				return E_SHAPE_AABB;
			}
		}*/

		class PhysicsManager;
		class Shape
		{

		public:

			virtual void set_radius(float raidus) {};
			virtual void set_dimensions(float width, float height) {};


		protected:
			Shape() = default;
			Shape(ShapeType type) : type_(type) , next_(nullptr){}
			virtual ~Shape();

			virtual void Reset()=0;

		private:

			inline void set_next(Shape* next) { next_ = next; };
			inline void set_id(int id) { id_ = id; };
			inline int get_id() { return id_ ; };
			inline ShapeType get_type() { return type_; };

			inline Shape* get_next() { return next_; };

		private:
			friend class PhysicsManager;

			int id_;
			ShapeType type_;
			Shape* next_;
		};


	}
}

#endif // !_SHAPE_H_
