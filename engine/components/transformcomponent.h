#ifndef _TRANSFORM_COMPONENT_H_
#define _TRANSFORM_COMPONENT_H_

#include "maincomponent.h"
#include "../maths/vector2D.h"

namespace enginecore {

	namespace component {

		class ComponentManager;
		class ObjectFactory;

		class TransformComponent : public MainComponent
		{

		public:

			void SetPositionX(float _x);
			void SetPositionY(float _y);

			void SetPosition(math::Vector2D position);

			float get_position_x() { return position_.x_;};
			float get_position_y() { return position_.y_; };

			inline math::Vector2D get_position() { return position_; };

		private:
			virtual void Update();
			virtual void Init(GameObject* owner);

			TransformComponent();
			~TransformComponent();

		private:
			friend class ComponentManager;
			friend class ObjectFactory;

			math::Vector2D position_;

			float scale_x_;
			float scale_y_;

		};

	}
}

#endif // !_TRANSFORM_COMPONENT_H_
