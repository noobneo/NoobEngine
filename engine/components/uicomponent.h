#ifndef _UI_COMPONENT_H_
#define _UI_COMPONENT_H_

#include "maincomponent.h"


namespace enginecore {

	namespace events {

		class Event;
	}
}

namespace enginecore {

	namespace component {

		class ComponentManager;
		class ObjectFactory;
		class RenderComponent;
		class GameObject;

		class UiComponent : public MainComponent
		{

		private:
			virtual void Update();
			virtual void Init(GameObject* owner);

			UiComponent();
			~UiComponent();
			UiComponent(const UiComponent &) = delete;
			UiComponent  & operator=(const UiComponent &) = delete;

			virtual void Reset();
			virtual void HandleEvent(events::Event *event);


		private:
			friend class ComponentManager;
			friend class ObjectFactory;

			RenderComponent* render_;

		};

	}
}

#endif // _UI_COMPONENT_H_
