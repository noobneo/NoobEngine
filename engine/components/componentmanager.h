#ifndef _COMPONENT_MANAGER_H_
#define _COMPONENT_MANAGER_H_

namespace enginecore {

	namespace component {

		class MainComponent;
		class GameobjectManager;

		class ComponentManager
		{

			void Update();
			void GetComponent();
		private:
			ComponentManager();
			~ComponentManager();

			void UpdateRenderComponents();
			void UpdateTransformComponents();
			void UpdatePhysicsComponents();
			void UpdateControllerComponent();
			void UpdateDebugDrawComponent();
		
		private:

			friend class GameobjectManager;


		};

	}
}

#endif // !_COMPONENT_MANAGER_H_
