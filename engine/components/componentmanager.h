#ifndef _COMPONENT_MANAGER_H_
#define _COMPONENT_MANAGER_H_


/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: componentmanager.h
Purpose: manages the components for the gameobjects
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 16th October 2017
---------------------------------------------------------*/



#include <unordered_map>


namespace enginecore {

	namespace common {

		class SceneManager;
	}
}

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


			void Reset();

			void LoadComponents();
			void LoadRender();
			void LoadPhyics();
			void LoadTransform();
			void LoadController();
			void LoadAnimation();
			void LoadWeapon();
			void LoadMouseComponent();
			void LoadAiComponents();
			void LoadBulletComponent();
			void LoadCameraComponent();
			void LoadButtonComponent();
			void LoadDebugDrawComponent();
			void LoadHealthComponent ();
			void LoadHommingMissileComponent();
		

			void UpdateRenderComponents();
			void UpdateTransformComponents();
			void UpdatePhysicsComponents();
			void UpdateControllerComponent();
			void UpdateDebugDrawComponent();
			void UpdateAnimationComponent();
			void UpdateWeaponComponent();
			void UpdateAiComponent();
			void UpdateMouseComponent();
			void UpdateBulletComponent();
			void UpdateCameraComponent();
			void UpdateButtonComponent();
			void UpdateHealthComponent();
			void UpdateHommingMissilComponent();
			
		
			MainComponent* GetBodyAnimationComponent(int id);
			MainComponent* GetBodyComponent( int id);
			MainComponent* GetRenderComponent( int id);
			MainComponent* GetTransformComponent(int id);

			//temp
			MainComponent* GetControllerComponent(int id);
			MainComponent* GetAnimationComponent(int id);
			MainComponent* GetWeaponComponent(int id);
			MainComponent* GetMouseComponent(int id);
			MainComponent* GetBulletComponent(int id);
			MainComponent* GetCameraComponent(int id);
			MainComponent* GetButtonComponent(int id);
			MainComponent* GetDebugDrawComponent(int id);
			MainComponent* GetEnemyAi1Component(int id);
			MainComponent* GetEnemyAi2Component(int id);
			MainComponent* GetEnemyBossAiComponent(int id);
			MainComponent* GetHealthComponent(int id);
			MainComponent* GetHommingMissileComponent(int id);

		private:

			friend class ObjectFactory;
			friend class common::SceneManager;

			static ComponentManager* instance_;

			int counter_;
			int total_active_body_components_;
			int total_active_shape_componentss_;
			int total_active_render_components_;
			int total_active_transform_components_;
			int total_active_controller_components_;
			//temp
			int total_active_animation_components_;
			int total_active_body_animation_component_;
			int total_active_weapon_component_;
			int total_active_mouse_component_;
			int total_active_ai1_component_;
			int total_active_ai2_component_;
			int total_active_bossai_component_;
			int total_active_bullet_component_;
			int total_active_camera_component_;
			int total_button_component_;
			int total_active_debugdraw_component_;
			int total_health_component_;
			int total_active_homming_missile_;

			MainComponent* body_		[MAX_SIZE];
			MainComponent* shape_		[MAX_SIZE];
			MainComponent* render_		[MAX_SIZE];
			MainComponent* transform_	[MAX_SIZE];
			MainComponent* controller_	[MAX_SIZE];
			MainComponent* health_		[MAX_SIZE];
			//
			MainComponent* camera_[1];
			MainComponent* ai1_[MAX_SIZE];
			MainComponent* ai2_[MAX_SIZE];
			MainComponent* bossai_[MAX_SIZE];
			MainComponent* mouse_[MAX_SIZE];
			MainComponent* button_[MAX_SIZE];
			MainComponent* weapon_[MAX_SIZE];
			MainComponent* bullet_[MAX_SIZE];
			MainComponent* animation_[MAX_SIZE];
			MainComponent* debug_draw_[MAX_SIZE];
			MainComponent* body_animation_[MAX_SIZE];
			MainComponent* homming_missile_[MAX_SIZE];
		

			MainComponent* available_body_component_;
			MainComponent* available_shape_component_;
			MainComponent* available_render_component_;
			MainComponent* available_transform_component_;
			MainComponent* available_controller_component_;
			MainComponent* available_health_component_;
			//temp
			MainComponent* available_animation_component_;
			MainComponent* available_body_animation_component_;
			MainComponent* available_weapon_component_;
			MainComponent* available_mouse_component_;
			MainComponent* available_ai1_component_;
			MainComponent* available_ai2_component_;
			MainComponent* available_bossai_component_;
			MainComponent* available_bullet_component_;
			MainComponent* available_camera_component_;
			MainComponent* available_button_component_;
			MainComponent* available_debugdraw_component_;
			MainComponent* available_homming_missle_component_;


			std::unordered_map<int , MainComponent*>	active_body_component_;
			std::unordered_map<int, MainComponent*>		active_shape_component_;
			std::unordered_map<int , MainComponent*>	active_render_component_;
			std::unordered_map<int , MainComponent*>	active_transform_component_;
			std::unordered_map<int , MainComponent*>	active_controller_component_;
			std::unordered_map<int, MainComponent*>		active_animation_component_;

			std::unordered_map<int, MainComponent*>		active_body_animation_component_;
			std::unordered_map<int, MainComponent*>		active_weapon_component_;
			std::unordered_map<int, MainComponent*>		active_mouse_component_;
			std::unordered_map<int, MainComponent*>		active_ai1_component_;
			std::unordered_map<int, MainComponent*>		active_ai2_component_;
			std::unordered_map<int, MainComponent*>		active_bossai_component_;

			std::unordered_map<int, MainComponent*>		active_bullet_component_;
			std::unordered_map<int, MainComponent*>		active_camera_component_;
			std::unordered_map<int, MainComponent*>		active_button_component_;
			std::unordered_map<int, MainComponent*>		active_debug_draw_;
			std::unordered_map<int, MainComponent*>		active_health_component_;
			std::unordered_map<int, MainComponent*>		active_homming_missile_component_;

			bool is_body_components_loaded_;
			bool is_shape_components_loaded_;
			bool is_render_components_loaded_;
			bool is_transform_components_loaded_;
			bool is_controller_components_loaded_;
			bool is_animation_components_loaded_;
			bool is_body_animation_components_loaded_;
			bool is_weapon_components_loaded_;
			bool is_mouse_components_loaded_;
			bool is_ai2_components_loaded_;
			bool is_ai1_components_loaded_;
			bool is_bossai_components_loaded_;
			bool is_bullet_components_loaded_;
			bool is_camera_component_loaded_;
			bool is_button_component_loaded_;
			bool is_debugdraw_loaded_;
			bool is_health_loaded_;
			bool is_homming_loaded_;
		};

	}
}

#endif // !_COMPONENT_MANAGER_H_
