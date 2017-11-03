#ifndef _PHYSICS_COMPONENT_H_
#define _PHYSICS_COMPONENT_H_

#include "maincomponent.h"

namespace enginecore {

	namespace component {


		class ComponentManager;

		class PhysicsComponent : public MainComponent
		{

		public :

		private:
			PhysicsComponent();
			~PhysicsComponent();

			virtual void Update();
			virtual void Init();
		private:
			friend class ComponentManager;
		};

	}
}


#endif // !_PHYSICS_COMPONENT_H_
