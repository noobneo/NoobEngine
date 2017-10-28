#ifndef _TRANSFORM_COMPONENT_H_
#define _TRANSFORM_COMPONENT_H_

#include "maincomponent.h"

namespace enginecore {

	namespace component {

		class ComponentManager;
		class TransformComponent : public MainComponent
		{
		public:
			virtual void Update();

			TransformComponent();
			~TransformComponent();

		private:
			friend class ComponentManager;
		};

	}
}

#endif // !_TRANSFORM_COMPONENT_H_
