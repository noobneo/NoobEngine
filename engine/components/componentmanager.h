#ifndef _COMPONENT_MANAGER_H_
#define _COMPONENT_MANAGER_H_

#include "component-types.h"
#include <unordered_map>

namespace enginecore {

	namespace component {

		class MainComponent;
		class GameobjectManager;

		class ComponentManager
		{


			void Update();
			void Destroy();
			void RemoveAllActiveComponents();

		private:
			ComponentManager();
			~ComponentManager()=default;

			ComponentManager(const ComponentManager& copy) = delete;
			void operator=(const ComponentManager& copy) = delete;

			void LoadComponents();
			void LoadRender();
			void LoadPhyics();
			void LoadTransform();



			void UpdateRenderComponents();
			void UpdateTransformComponents();
			void UpdatePhysicsComponents();
			void UpdateControllerComponent();
			void UpdateDebugDrawComponent();
		


			MainComponent* GetPhysicsComponent(ComponentType type , int id);
			MainComponent* GetRenderComponent(ComponentType type, int id);
			MainComponent* GetTransformComponent(ComponentType type, int id);


		private:

			friend class GameobjectManager;//check again

			int total_active_render_components_;
			int total_active_physics_components_;
			int total_active_transform_components_;

			MainComponent* render_		[MAX_SIZE];
			MainComponent* physics_		[MAX_SIZE];
			MainComponent* transform_	[MAX_SIZE];
			MainComponent* controller_	[MAX_SIZE];

			MainComponent* available_render_component_;
			MainComponent* available_physics_component_;
			MainComponent* available_transform_component_;
			MainComponent* available_controller_component_;

			std::unordered_map<int , MainComponent*>	active_render_component_;
			std::unordered_map<int , MainComponent*>	active_physics_component_;
			std::unordered_map<int , MainComponent*>	active_transform_component_;
			std::unordered_map<int , MainComponent*>	active_controller_component_;
			
		};

	}
}

#endif // !_COMPONENT_MANAGER_H_
