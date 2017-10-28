#ifndef _CONTROLLER_COMPONENT_H_
#define _CONTROLLER_COMPONENT_H_

#include "maincomponent.h"

namespace enginecore {

	namespace component {
		
		class ComponentManager;

		class ControllerComponent : public MainComponent
		{

		public:

			virtual void Update();

		private:
			ControllerComponent();
			~ControllerComponent();

		private:
			friend class ComponentManager;
		};
	}
}

#endif // !_CONTROLLER_COMPONENT_H_
