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


			/*
			* @function : set_radius(float radius)
			* @brief: method for setting the dimension of circle shape
			*/
			virtual void set_radius(float raidus) {};
			
			/*
			* @function : set_dimensions(float width, float height) 
			* @brief: method for setting the dimension of aabb
			*/
			virtual void set_dimensions(float width, float height) {};


		protected:
			//ctor
			Shape() = default;
			Shape(ShapeType type) : type_(type) , next_(nullptr){}
			
			//dtor
			virtual ~Shape();

			/*
			* @function : Reset()
			* @brief: virtual method for reseting respective shape
			*/
			virtual void Reset()=0;

		private:

			//setters
			inline void set_next(Shape* next) { next_ = next; };
			inline void set_id(int id) { id_ = id; };
			
			//getters
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
