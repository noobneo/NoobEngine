#ifndef _SHAPE_COMPONENT_H_
#define _SHAPE_COMPONENT_H_

#include "maincomponent.h"

namespace enginecore {

	namespace component {

		class GameObject;

		class ShapeComponent : public MainComponent
		{


		private:
			ShapeComponent();
			~ShapeComponent()=default;


			virtual void Update();
			virtual void Init(GameObject* owner);


		private:
			friend class ComponentManager;
			friend class ObjectFactory;


	
		};



	}
}

#endif // !_SHAPE_COMPONENT_H_
