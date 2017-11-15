#ifndef _CONTROLLER_COMPONENT_H_
#define _CONTROLLER_COMPONENT_H_

#include "maincomponent.h"
#include "../../external/SDL2.0 Lib/include/SDL_stdinc.h"

namespace enginecore {

	namespace component {
		
		class ComponentManager;
		class ObjectFactory;
		class BodyComponent;

		class ControllerComponent : public MainComponent
		{

		private:
			ControllerComponent();
			~ControllerComponent();


			virtual void Update();
			virtual void Init(GameObject* owner);
			virtual void Reset();

#ifdef TEST_MODE

			void RegisterKeyBoardListener();
			void OnKeyPressed(const Uint8 * key_state);
			void OnKeyReleased(const Uint8 * key_state);
#endif

		private:
			friend class ComponentManager;
			friend class ObjectFactory;

			BodyComponent* body_component_;
			bool is_airborne_;
		};
	}
}

#endif // !_CONTROLLER_COMPONENT_H_
