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



#include "component-includesh.h"
#include "../common/macros.h"
#include "../enginelogger/enginelogger.h"
#include "gameobject.h"

namespace enginecore {

	namespace component {


		ComponentManager* ComponentManager::instance_ = nullptr;

		ComponentManager::ComponentManager() {

			counter_ = 0;
			available_body_component_		= nullptr;
			available_shape_component_		= nullptr;
			available_render_component_		= nullptr;
			available_transform_component_	= nullptr;
			available_controller_component_ = nullptr;
			available_animation_component_	= nullptr;
			available_body_animation_component_ = nullptr;
			available_weapon_component_ = nullptr;
			available_ai1_component_ = nullptr;
			available_ai2_component_ = nullptr;
			available_bossai_component_ = nullptr;
			available_mouse_component_ = nullptr;
			available_bullet_component_ = nullptr;
			available_camera_component_ = nullptr;
			available_button_component_ = nullptr;
			available_debugdraw_component_ = nullptr;
			available_health_component_ = nullptr;
			available_homming_missle_component_ = nullptr;


			is_body_components_loaded_		= false;
			is_shape_components_loaded_		= false;
			is_render_components_loaded_	= false;
			is_transform_components_loaded_ = false;
			is_controller_components_loaded_= false;
			is_animation_components_loaded_ = false;
			is_body_animation_components_loaded_ = false;
			is_weapon_components_loaded_ = false;
			is_ai1_components_loaded_ = false;
			is_ai2_components_loaded_ = false;
			is_bossai_components_loaded_ = false;
			is_mouse_components_loaded_ = false;
			is_bullet_components_loaded_ = false;
			is_camera_component_loaded_ = false;
			is_button_component_loaded_ = false;
			is_debugdraw_loaded_ = false;
			is_health_loaded_ = false;
			is_homming_loaded_ = false;



			LoadComponents();
		}

		ComponentManager* ComponentManager::GetInstance() {

			if (!ComponentManager::instance_) {

				ComponentManager::instance_ = new ComponentManager();
			}

			return ComponentManager::instance_;
		}

		void ComponentManager::LoadComponents() {

			LoadRender();
			LoadPhyics();
			LoadTransform();
			LoadController();
			LoadAnimation();
			LoadWeapon();
			LoadHealthComponent();
			LoadAiComponents();
			LoadMouseComponent();
			LoadBulletComponent();
			LoadCameraComponent();
			LoadButtonComponent();
			LoadDebugDrawComponent();
			LoadHommingMissileComponent();
		}


		void ComponentManager::LoadAiComponents() {
	
			
			for (int i = 0; i < MAX_SIZE; ++i) {

				bossai_[i] = new BossAi();
				bossai_[i]->set_id(i+ ++counter_);
				bossai_[i]->set_next(available_bossai_component_);
				bossai_[i]->set_component_type(E_COMPONENT_TYPE_ENEMY_BOSS);
				available_bossai_component_ = bossai_[i];
			}
			is_bossai_components_loaded_ = true;

			for (int i = 0; i < MAX_SIZE; ++i) {

				ai1_[i] = new Enemy1AI();
				ai1_[i]->set_id(i + ++counter_);
				ai1_[i]->set_next(available_ai1_component_);
				ai1_[i]->set_component_type(E_COMPONENT_TYPE_ENEMY_AI1);
				available_ai1_component_ = ai1_[i];
			}
			is_ai1_components_loaded_ = true;

			/*for (int i = 0; i < MAX_SIZE; ++i) {

				ai2_[i] = new Enemy1AI();
				ai2_[i]->set_id(i);
				ai2_[i]->set_next(available_ai2_component_);
				ai2_[i]->set_component_type(E_COMPONENT_TYPE_ENEMY_AI2);
				available_ai2_component_ = ai2_[i];
			}
			is_ai2_components_loaded_ = true;*/


		}

		void ComponentManager::LoadMouseComponent() {

			for (int i = 0; i < MAX_SIZE; ++i) {

				mouse_[i] = new MouseComponent();
				mouse_[i]->set_id(i + ++counter_);
				mouse_[i]->set_next(available_mouse_component_);
				mouse_[i]->set_component_type(E_COMPONENT_TYPE_MOUSE);
				available_mouse_component_ = mouse_[i];
			}
			is_mouse_components_loaded_ = true;
		}


		void ComponentManager::LoadHommingMissileComponent() {

			for (int i = 0; i < MAX_SIZE; ++i) {

				homming_missile_[i] = new HomingMissile();
				homming_missile_[i]->set_id(i + ++counter_);
				homming_missile_[i]->set_next(available_homming_missle_component_);
				homming_missile_[i]->set_component_type(E_COMPONENT_HOMMING_MISSILE);
				available_homming_missle_component_ = homming_missile_[i];
			}
			is_homming_loaded_ = true;
		}

		void ComponentManager::LoadHealthComponent() {

			for (int i = 0; i < MAX_SIZE; ++i) {

				health_[i] = new HealthComponent();
				health_[i]->set_id(i + ++counter_);
				health_[i]->set_next(available_health_component_);
				health_[i]->set_component_type(E_COMPONENT_TYPE_HEALTH);
				available_health_component_ = health_[i];
			}
			is_health_loaded_ = true;
		}




		void ComponentManager::LoadDebugDrawComponent() {

			for (int i = 0; i < MAX_SIZE; ++i) {

				debug_draw_[i] = new BoundingBoxComponent();
				debug_draw_[i]->set_id(i + ++counter_);
				debug_draw_[i]->set_next(available_debugdraw_component_);
				debug_draw_[i]->set_component_type(E_COMPONENT_TYPE_DEBUG_DRAW);
				available_debugdraw_component_ = debug_draw_[i];
			}
			is_debugdraw_loaded_ = true;
		}



		void ComponentManager::LoadButtonComponent() {

			for (int i = 0; i < MAX_SIZE; ++i) {

				button_[i] = new ButtonComponent();
				button_[i]->set_id(i + ++counter_);
				button_[i]->set_next(available_button_component_);
				button_[i]->set_component_type(E_COMPONENT_TYPE_BUTTONS);
				available_button_component_ = button_[i];
			}
			is_button_component_loaded_ = true;
		}


		void ComponentManager::LoadCameraComponent() {

			for (int i = 0; i < 1; ++i) {

				camera_[i] = new CameraComponent();
				camera_[i]->set_id(i + ++counter_);
				camera_[i]->set_next(available_camera_component_);
				camera_[i]->set_component_type(E_COMPONENT_TYPE_CAMERA);
				available_camera_component_ = camera_[i];
			}
			is_camera_component_loaded_ = true;
		}


		void ComponentManager::LoadBulletComponent() {

			for (int i = 0; i < MAX_SIZE; ++i) {

				bullet_[i] = new BulletComponent();
				bullet_[i]->set_id(i);
				bullet_[i]->set_next(available_bullet_component_);
				bullet_[i]->set_component_type(E_COMPONENT_TYPE_BULLET);
				available_bullet_component_ = bullet_[i];
			}
			is_bullet_components_loaded_ = true;
		}



		void ComponentManager::LoadRender() {

			for (int i = 0; i < MAX_SIZE; ++i) {

				render_[i] = new RenderComponent();
				render_[i]->set_id(i + ++counter_);
				render_[i]->set_next(available_render_component_);
				render_[i]->set_component_type(E_COMPONENT_TYPE_RENDER);
				available_render_component_ = render_[i];
			}
			is_render_components_loaded_ = true;
		}

		void ComponentManager::LoadPhyics() {


			for (int i = 0; i < MAX_SIZE; ++i) {

				shape_[i] = new ShapeComponent();
				shape_[i]->set_id(i + ++counter_);
				shape_[i]->set_next(available_shape_component_);
				shape_[i]->set_component_type(E_COMPONENT_TYPE_SHAPE);
				available_shape_component_ = shape_[i];
			}
			is_shape_components_loaded_ = true;


			for (int i = 0; i < MAX_SIZE; ++i) {

				body_[i] = new BodyComponent();
				body_[i]->set_id(i + ++counter_);
				body_[i]->set_next(available_body_component_);
				body_[i]->set_component_type(E_COMPONENT_TYPE_BODY);
				available_body_component_ = body_[i];
			}
			is_body_components_loaded_ = true;
		}

		void ComponentManager::LoadTransform() {

			for (int i = 0; i < MAX_SIZE; ++i) {

				transform_[i] = new TransformComponent();
				transform_[i]->set_id(i + ++counter_);
				transform_[i]->set_next(available_transform_component_);
				transform_[i]->set_component_type(E_COMPONENT_TYPE_TRANSFORM);
				available_transform_component_ = transform_[i];
			}

			is_transform_components_loaded_ = true;
		}

		void ComponentManager::LoadController() {

			for (int i = 0; i < MAX_SIZE; ++i) {

				controller_[i] = new ControllerComponent();
				controller_[i]->set_id(i + ++counter_);
				controller_[i]->set_next(available_controller_component_);
				controller_[i]->set_component_type(E_COMPONENT_TYPE_TRANSFORM);
				available_controller_component_ = controller_[i];
			}

			is_controller_components_loaded_ = true;
		}

		void ComponentManager::LoadAnimation() {

			for (int i = 0; i < MAX_SIZE; ++i) {

				animation_[i] = new AnimationComponent();
				animation_[i]->set_id(i + ++counter_);
				animation_[i]->set_next(available_animation_component_);
				animation_[i]->set_component_type(E_COMPONENT_TYPE_ANIMATION);
				available_animation_component_ = animation_[i];
			}

			is_animation_components_loaded_ = true;

			for (int i = 0; i < MAX_SIZE; ++i) {

				body_animation_[i] = new BodyAnimationComponent();
				body_animation_[i]->set_id(i + ++counter_);
				body_animation_[i]->set_next(available_body_animation_component_);
				body_animation_[i]->set_component_type(E_COMPONENT_TYPE_BODY_ANIMATION);
				available_body_animation_component_ = body_animation_[i];
			}

			is_body_animation_components_loaded_ = true;


		}

		void ComponentManager::LoadWeapon() {

			for (int i = 0; i < MAX_SIZE; ++i) {

				weapon_[i] = new WeaponComponent();
				weapon_[i]->set_id(i + ++counter_);
				weapon_[i]->set_next(available_weapon_component_);
				weapon_[i]->set_component_type(E_COMPONENT_TYPE_ANIMATION);
				available_weapon_component_ = weapon_[i];
			}

			is_weapon_components_loaded_ = true;
		}

		MainComponent* ComponentManager::GetControllerComponent(int id) {

			if (!available_controller_component_) {

				ENGINE_ERR_LOG("No Transform Component Available yet");
			}

			MainComponent* temp = available_controller_component_;
			available_controller_component_ = available_controller_component_->get_next();
			active_controller_component_[id] = temp;
			return temp;
		}

		MainComponent* ComponentManager::GetHommingMissileComponent(int id) {

			if (!available_homming_missle_component_) {

				ENGINE_ERR_LOG("No HOmmingMissile Component Available yet");
			}

			MainComponent* temp = available_homming_missle_component_;
			available_homming_missle_component_ = available_homming_missle_component_->get_next();
			active_homming_missile_component_[id] = temp;
			return temp;
		}

		MainComponent* ComponentManager::GetHealthComponent(int id) {

			if (!available_health_component_) {

				ENGINE_ERR_LOG("No Health Component Available yet");
			}

			MainComponent* temp = available_health_component_;
			available_health_component_ = available_health_component_->get_next();
			active_health_component_[id] = temp;
			return temp;
		}



		MainComponent* ComponentManager::GetMouseComponent(int id) {

			if (!available_mouse_component_) {

				ENGINE_ERR_LOG("No Mouse Component Available yet");
			}

			MainComponent* temp = available_mouse_component_;
			available_mouse_component_ = available_mouse_component_->get_next();
			active_mouse_component_[id] = temp;
			return temp;
		}

		MainComponent* ComponentManager::GetButtonComponent(int id) {

			if (!available_button_component_) {

				ENGINE_ERR_LOG("No BUtton Component Available yet");
			}

			MainComponent* temp = available_button_component_;
			available_button_component_ = available_button_component_->get_next();
			active_button_component_[id] = temp;
			return temp;
		}


		MainComponent* ComponentManager::GetDebugDrawComponent(int id) {

			if (!available_debugdraw_component_) {

				ENGINE_ERR_LOG("No DebugDraw Component Available yet");
			}

			MainComponent* temp = available_debugdraw_component_;
			available_debugdraw_component_ = available_debugdraw_component_->get_next();
			active_debug_draw_[id] = temp;
			return temp;
		}



		MainComponent* ComponentManager::GetCameraComponent(int id) {

			if (!available_camera_component_) {

				ENGINE_ERR_LOG("No Camera Component Available yet");
			}

			MainComponent* temp = available_camera_component_;
			available_camera_component_ = available_camera_component_->get_next();
			active_camera_component_[id] = temp;
			return temp;
		}


		MainComponent* ComponentManager::GetEnemyBossAiComponent(int id) {

			if (!available_bossai_component_) {

				ENGINE_ERR_LOG("No Boss Component Available yet");
			}

			MainComponent* temp = available_bossai_component_;
			available_bossai_component_ = available_bossai_component_->get_next();
			active_bossai_component_[id] = temp;
			return temp;
		}

		MainComponent* ComponentManager::GetEnemyAi1Component(int id) {

			
			if (!available_ai1_component_) {

				ENGINE_ERR_LOG("No Ai1 Component Available yet");
			}

			MainComponent* temp = available_ai1_component_;
			available_ai1_component_ = available_ai1_component_->get_next();
			active_ai1_component_[id] = temp;
			return temp;
		}

		MainComponent* ComponentManager::GetEnemyAi2Component(int id) {

			
			if (!available_ai2_component_) {

				ENGINE_ERR_LOG("No Ai2 Component Available yet");
			}

			MainComponent* temp = available_ai2_component_;
			available_ai2_component_ = available_ai2_component_->get_next();
			active_ai2_component_[id] = temp;
			return temp;
		}





		MainComponent* ComponentManager::GetBulletComponent(int id) {

			if (!available_bullet_component_) {

				ENGINE_ERR_LOG("No Bullet Component Available yet");
			}

			MainComponent* temp = available_bullet_component_;
			available_bullet_component_ = available_bullet_component_->get_next();
			active_bullet_component_[id] = temp;
			return temp;
		}


		MainComponent* ComponentManager::GetBodyComponent(int id) {

			if (!available_body_component_) {
				
				ENGINE_ERR_LOG("No Body and Shape Component Available yet");
			} 

			MainComponent* body_temp = available_body_component_;
			available_body_component_ = available_body_component_->get_next();
			active_body_component_[id] = body_temp;


			MainComponent* shape_temp = available_shape_component_;
			available_shape_component_ = available_shape_component_->get_next();
			active_shape_component_[id] = shape_temp;

			/*attach body and shape*/
			((BodyComponent*)body_temp)->set_shape_component((ShapeComponent*)shape_temp);
			((ShapeComponent*)shape_temp)->set_body_component((BodyComponent*)body_temp);

			return body_temp;
		}

		MainComponent* ComponentManager::GetRenderComponent(int id) {

			if (!available_render_component_) {

				ENGINE_ERR_LOG("No Transform Component Available yet");
			}

			MainComponent* temp = available_render_component_;
			available_render_component_ = available_render_component_->get_next();
			active_render_component_[id] = temp;
			return temp;
		}


		MainComponent* ComponentManager::GetTransformComponent(int id) {

			if (!available_transform_component_) {

				ENGINE_ERR_LOG("No Transform Component Available yet");
			}

			MainComponent* temp = available_transform_component_;
			available_transform_component_ = available_transform_component_->get_next();
			active_transform_component_[id] = temp;
			return temp;
		}

		MainComponent* ComponentManager::GetAnimationComponent(int id) {

			if (!available_animation_component_) {

				ENGINE_ERR_LOG("No Animation Component Available yet");
			}

			MainComponent* temp = available_animation_component_;
			available_animation_component_ = available_animation_component_->get_next();
			active_animation_component_[id] = temp;
			return temp;
		}

		
		MainComponent* ComponentManager::GetBodyAnimationComponent(int id) {

			if (!available_body_animation_component_) {

				ENGINE_ERR_LOG("Oops no body animatino component");
			}

			MainComponent* temp = available_body_animation_component_;
			available_body_animation_component_ = available_body_animation_component_->get_next();
			active_body_animation_component_[id] = temp;
			return temp;
		}

		MainComponent* ComponentManager::GetWeaponComponent(int id) {

			if (!available_weapon_component_) {

				ENGINE_ERR_LOG("No Weapon Component Available yet");
			}

			MainComponent* temp = available_weapon_component_;
			available_weapon_component_ = available_weapon_component_->get_next();
			active_weapon_component_[id] = temp;
			return temp;
		}



		void ComponentManager::Update() {

			UpdateButtonComponent();
			UpdateRenderComponents();
			UpdatePhysicsComponents();
			UpdateAnimationComponent();
			UpdateWeaponComponent();
			UpdateAiComponent();
			UpdateMouseComponent();
			UpdateBulletComponent();
			UpdateCameraComponent();
			UpdateDebugDrawComponent();
			UpdateHealthComponent();
			UpdateHommingMissilComponent();
		}

		void ComponentManager::UpdateRenderComponents() {

			for (auto &itr : active_render_component_) {

				itr.second->Update();
			}
		}

		void ComponentManager::UpdateHealthComponent() {

			for (auto &itr : active_health_component_) {

				itr.second->Update();
			}
		}

		void ComponentManager::UpdateHommingMissilComponent() {

			for (auto &itr : active_homming_missile_component_) {

				itr.second->Update();
			}
		}



		void ComponentManager::UpdateButtonComponent() {


		}




		void ComponentManager::UpdateCameraComponent() {

			for (auto &itr : active_camera_component_) {

				itr.second->Update();
			}
		}


		void ComponentManager::UpdateWeaponComponent() {

			for (auto &itr : active_weapon_component_) {

				itr.second->Update();
			}
		}

		void ComponentManager::UpdateTransformComponents() {


		}

		void ComponentManager::UpdateBulletComponent() {


		}

		void ComponentManager::UpdatePhysicsComponents() {

		}

		void ComponentManager::UpdateControllerComponent() {


		}

		void ComponentManager::UpdateDebugDrawComponent() {

			for (auto &itr : active_debug_draw_) {

				itr.second->Update();
			}
		}

		void ComponentManager::UpdateAiComponent() {

			for (auto &itr : active_ai1_component_) {

				itr.second->Update();
			}

			for (auto &itr : active_ai2_component_) {

				itr.second->Update();
			}

			for (auto &itr : active_bossai_component_) {

				itr.second->Update();
			}
		}

		void ComponentManager::UpdateMouseComponent() {


		}

		void ComponentManager::UpdateAnimationComponent() {

			for (auto &itr : active_animation_component_) {

				itr.second->Update();
			}

			for (auto &itr : active_body_animation_component_) {

				itr.second->Update();
			}
		}

		void ComponentManager::UnloadComponents() {

			Destroy();
		}

		void ComponentManager::Reset() {

			//transform
			for (auto &itr : active_transform_component_) {

				itr.second->Reset();
				itr.second->set_next(available_transform_component_);
				available_transform_component_ = itr.second;
			}

			//body
			for (auto &itr : active_body_component_) {

				itr.second->Reset();
				itr.second->set_next(available_body_component_);
				available_body_component_ = itr.second;
			}

			//shape
			for (auto &itr : active_shape_component_) {

				itr.second->Reset();
				itr.second->set_next(available_shape_component_);
				available_shape_component_ = itr.second;
			}
			//controller
			for (auto &itr : active_controller_component_) {

				itr.second->Reset();
				itr.second->set_next(available_controller_component_);
				available_controller_component_ = itr.second;
			}
			//animation
			for (auto &itr : active_animation_component_) {

				itr.second->Reset();
				itr.second->set_next(available_animation_component_);
				available_animation_component_ = itr.second;
			}
			//render
			for (auto &itr : active_render_component_) {

				itr.second->Reset();
				itr.second->set_next(available_render_component_);
				available_render_component_ = itr.second;
			}

			//body
			for (auto &itr : active_body_animation_component_) {

				itr.second->Reset();
				itr.second->set_next(available_body_animation_component_);
				available_body_animation_component_ = itr.second;
			}
	
			//weapon
			for (auto &itr : active_weapon_component_) {

				itr.second->Reset();
				itr.second->set_next(available_weapon_component_);
				available_weapon_component_ = itr.second;
			}

			//ai
			for (auto &itr : active_ai1_component_) {

				itr.second->Reset();
				itr.second->set_next(available_ai1_component_);
				available_ai1_component_ = itr.second;
			}

			for (auto &itr : active_ai2_component_) {

				itr.second->Reset();
				itr.second->set_next(available_ai2_component_);
				available_ai2_component_ = itr.second;
			}

			for (auto &itr : active_bossai_component_) {

				itr.second->Reset();
				itr.second->set_next(available_bossai_component_);
				available_bossai_component_ = itr.second;

			}

			//mouse
			for (auto &itr : active_mouse_component_) {

				itr.second->Reset();
				itr.second->set_next(available_mouse_component_);
				available_mouse_component_ = itr.second;
			}

			//mouse
			for (auto &itr : active_bullet_component_) {

				itr.second->Reset();
				itr.second->set_next(available_bullet_component_);
				available_bullet_component_ = itr.second;
			}


			//camera
			for (auto &itr : active_camera_component_) {

				itr.second->Reset();
				itr.second->set_next(available_camera_component_);
				available_camera_component_ = itr.second;
			}




			//button
			for (auto &itr : active_button_component_) {

				itr.second->Reset();
				itr.second->set_next(available_button_component_);
				available_button_component_ = itr.second;
			}


			//debug
			for (auto &itr : active_debug_draw_) {

				itr.second->Reset();
				itr.second->set_next(available_debugdraw_component_);
				available_debugdraw_component_ = itr.second;
			}

			//health
			for (auto &itr : active_health_component_) {

				itr.second->Reset();
				itr.second->set_next(available_health_component_);
				available_health_component_ = itr.second;
			}

			//homming missle
	
			for (auto &itr : active_homming_missile_component_) {

				itr.second->Reset();
				itr.second->set_next(available_homming_missle_component_);
				available_homming_missle_component_ = itr.second;
			}



			RemoveAllActiveComponents();
		}


		void ComponentManager::RemoveAllActiveComponents() {

			active_body_component_.clear();
			active_shape_component_.clear();
			active_render_component_.clear();
			active_transform_component_.clear();
			active_controller_component_.clear();
			active_animation_component_.clear();
			active_body_animation_component_.clear();
			active_weapon_component_.clear();
			active_ai1_component_.clear();
			active_ai2_component_.clear();
			active_bossai_component_.clear();
			active_mouse_component_.clear();
			active_bullet_component_.clear();
			active_camera_component_.clear();
			active_button_component_.clear();
			active_debug_draw_.clear();
			active_health_component_.clear();
			active_homming_missile_component_.clear();

		}
		void ComponentManager::Destroy() {


			RemoveAllActiveComponents();//do something with ths

#ifdef TEST_MODE
			ENGINE_LOG("Destroying Component Manager");
#endif // TEST_MODE
		

			if (is_render_components_loaded_) {

				/*render components*/
				for (int i = 0; i < MAX_SIZE; i++) {

					delete render_[i];
				}
				is_render_components_loaded_ = false;
			}

			if (is_body_components_loaded_) {

				/*body components*/
				for (int i = 0; i < MAX_SIZE; i++) {

					delete body_[i];
				}
				is_body_components_loaded_ = false;
			}

			if (is_shape_components_loaded_) {

				/*shapes components*/
				for (int i = 0; i < MAX_SIZE; i++) {

					delete shape_[i];
				}
				is_shape_components_loaded_ = false;
			}



			if (is_transform_components_loaded_) {

				/*transform_ components*/
				for (int i = 0; i < MAX_SIZE; i++) {

					delete transform_[i];
				}
				is_transform_components_loaded_ = false;
			}


			if (is_controller_components_loaded_) {

				/*controller components*/
				for (int i = 0; i < MAX_SIZE; i++) {

					delete controller_[i];
				}
				is_controller_components_loaded_ = false;
			}


			if (is_animation_components_loaded_) {
				/*animation components*/
				for (int i = 0; i < MAX_SIZE; i++) {

					delete animation_[i];
				}
				is_animation_components_loaded_ = false;
			}



			if (is_body_animation_components_loaded_) {
				/*animation components*/
				for (int i = 0; i < MAX_SIZE; i++) {

					delete body_animation_[i];
				}
				is_body_animation_components_loaded_ = false;
			}


			if (is_weapon_components_loaded_) {
				/*weapon components*/
				for (int i = 0; i < MAX_SIZE; i++) {

					delete weapon_[i];
				}
				is_weapon_components_loaded_ = false;
			}



			if (is_ai1_components_loaded_) {
				/*ai components*/
				for (int i = 0; i < MAX_SIZE; i++) {

					delete ai1_[i];
				}
				is_ai1_components_loaded_ = false;
			}



				/*ai components*/
			/*if (is_ai2_components_loaded_) {
				for (int i = 0; i < MAX_SIZE; i++) {

					delete ai2_[i];
				}
				is_ai2_components_loaded_ = false;
			}
			*/


			if (is_bossai_components_loaded_) {
				/*ai components*/
				for (int i = 0; i < MAX_SIZE; i++) {

					delete bossai_[i];
				}
				is_bossai_components_loaded_ = false;
			}




			if (is_mouse_components_loaded_) {
				/*mouse components*/
				for (int i = 0; i < MAX_SIZE; i++) {

					delete mouse_[i];
				}
				is_mouse_components_loaded_ = false;
			}

			if (is_bullet_components_loaded_) {
				/*bullet components*/
				for (int i = 0; i < MAX_SIZE; i++) {

					delete bullet_[i];
				}
				is_bullet_components_loaded_ = false;
			}


			if (is_camera_component_loaded_) {
				/*camera components*/
				for (int i = 0; i < 1; i++) {

					delete camera_[i];
				}
				is_camera_component_loaded_ = false;
			}


			if (is_button_component_loaded_) {
				/*button components*/
				for (int i = 0; i < 1; i++) {

					delete button_[i];
				}
				is_button_component_loaded_ = false;
			}



			if (is_debugdraw_loaded_) {
				/*button components*/
				for (int i = 0; i < 1; i++) {

					delete debug_draw_[i];
				}
				is_debugdraw_loaded_ = false;
			}


			if (is_health_loaded_) {
				/*button components*/
				for (int i = 0; i < 1; i++) {

					delete health_[i];
				}
				is_health_loaded_ = false;
			}

			if (is_homming_loaded_) {
				/*button components*/
				for (int i = 0; i < 1; i++) {

					delete homming_missile_[i];
				}
				is_homming_loaded_ = false;
			}



			CLEAN_DELETE(ComponentManager::instance_);
		}
	}
}

