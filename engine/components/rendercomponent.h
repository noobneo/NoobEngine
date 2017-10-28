#ifndef _RENDER_COMPONENT_H_
#define _RENDER_COMPONENT_H_

#include "maincomponent.h"

namespace enginecore {

	namespace component {

		class ComponentManager;

		class RenderComponent : public MainComponent
		{
		public:
			virtual void Update();
		private:
			RenderComponent();
			~RenderComponent();

		private:
			friend class ComponentManager;
		};
	}
}

#endif // !_RENDER_COMPONENT_H_
