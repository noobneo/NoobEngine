#ifndef _MOUSE_COMPONENT_H_
#define _MOUSE_COMPONENT_H_

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
		class TransformComponent;
		class GameObject;

		class MouseComponent : public MainComponent
		{
		public:

			inline void set_follow_mouse(bool follow_mouse) { follow_mouse_ = follow_mouse; };

		private:
			virtual void Update();
			virtual void Init(GameObject* owner);

			MouseComponent();
			~MouseComponent();
			MouseComponent(const MouseComponent &) = delete;
			MouseComponent  & operator=(const MouseComponent &) = delete;

			void RegisterForMouseEvent();
			void MouseEvent(uint32_t type, int x, int y);

			virtual void Reset();
			virtual void HandleEvent(events::Event *event);


		private:
			friend class ComponentManager;
			friend class ObjectFactory;

			TransformComponent* transform_;
			bool follow_mouse_;

		};

	}
}

#endif // _BODY_ANIMATION_COMPONENT_H_
