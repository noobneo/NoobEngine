#ifndef _AABB_SHAPE_H_
#define _AABB_SHAPE_H_

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
