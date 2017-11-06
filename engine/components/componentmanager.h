#ifndef _COMPONENT_MANAGER_H_
#define _COMPONENT_MANAGER_H_

#include "component-types.h"
#include <unordered_map>

namespace enginecore {

	namespace component {

		class MainComponent;
		class ObjectFactory;

		class ComponentManager
		{

		public:

			static ComponentManager* GetInstance();
			void Update();
			void Destroy();
		
		private:
			ComponentManager();
			~ComponentManager()=default;

			ComponentManager(const ComponentManager& copy) = delete;
			void operator=(const ComponentManager& copy) = delete;

			void UnloadComponents();
			void RemoveAllActiveComponents();


			void LoadComponents();
			void LoadRender();
			void LoadPhyics();
			void LoadTransform();
			void LoadController();
			void LoadAnimation();


			void UpdateRenderComponents();
			void UpdateTransformComponents();
			void UpdatePhysicsComponents();
			void UpdateControllerComponent();
			void UpdateDebugDrawComponent();
			void UpdateAnimationComponent();
		

			MainComponent* GetPhysicsComponent( int id);
			MainComponent* GetRenderComponent( int id);
			MainComponent* GetTransformComponent(int id);

			//temp
			MainComponent* GetControllerComponent(int id);
			MainComponent* GetAnimationComponent(int id);

		private:

			friend class ObjectFactory;

			static ComponentManager* instance_;

			int total_active_render_components_;
			int total_active_physics_components_;
			int total_active_transform_components_;
			int total_active_controller_components_;
			//temp
			int total_active_animation_components_;

			MainComponent* render_		[MAX_SIZE];
			MainComponent* physics_		[MAX_SIZE];
			MainComponent* transform_	[MAX_SIZE];
			MainComponent* controller_	[MAX_SIZE];
			//
			MainComponent* animation_[MAX_SIZE];
		

			MainComponent* available_render_component_;
			MainComponent* available_physics_component_;
			MainComponent* available_transform_component_;
			MainComponent* available_controller_component_;
			//temp
			MainComponent* available_animation_component_;

			std::unordered_map<int , MainComponent*>	active_render_component_;
			std::unordered_map<int , MainComponent*>	active_physics_component_;
			std::unordered_map<int , MainComponent*>	active_transform_component_;
			std::unordered_map<int , MainComponent*>	active_controller_component_;
			std::unordered_map<int, MainComponent*>		active_animation_component_;

			bool is_render_components_loaded_;
			bool is_physics_components_loaded_;
			bool is_transform_components_loaded_;
			bool is_controller_components_loaded_;
			bool is_animation_components_loaded_;
			
		};

	}
}

#endif // !_COMPONENT_MANAGER_H_
