#include "componentmanager.h"
#include "rendercomponent.h"
#include "physicscomponent.h"
#include "transformcomponent.h"
#include "controllercomponent.h"

#include "../common/macros.h"
#include "../enginelogger/enginelogger.h"
#include "gameobject.h"

namespace enginecore {

	namespace component {


		ComponentManager* ComponentManager::instance_ = nullptr;

		ComponentManager::ComponentManager() {

			available_render_component_		= nullptr;
			available_physics_component_	= nullptr;
			available_transform_component_	= nullptr;
			available_controller_component_ = nullptr;

			is_render_components_loaded_	= false;
			is_physics_components_loaded_	= false;
			is_transform_components_loaded_ = false;
			is_controller_components_loaded_= false;

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
		}


		void ComponentManager::LoadRender() {

			for (int i = 0; i < MAX_SIZE; ++i) {

				render_[i] = new RenderComponent();
				render_[i]->set_id(i);
				render_[i]->set_next(available_render_component_);
				render_[i]->set_component_type(E_COMPONENT_TYPE_RENDER);
				available_render_component_ = render_[i];
			}
			is_render_components_loaded_ = true;
		}

		void ComponentManager::LoadPhyics() {

			for (int i = 0; i < MAX_SIZE; ++i) {

				physics_[i] = new PhysicsComponent();
				physics_[i]->set_id(i);
				physics_[i]->set_next(available_physics_component_);
				physics_[i]->set_component_type(E_COMPONENT_TYPE_PHYSICS);
				available_physics_component_ = physics_[i];
			}
			is_physics_components_loaded_ = true;
		}

		void ComponentManager::LoadTransform() {

			for (int i = 0; i < MAX_SIZE; ++i) {

				transform_[i] = new TransformComponent();
				transform_[i]->set_id(i);
				transform_[i]->set_next(available_transform_component_);
				transform_[i]->set_component_type(E_COMPONENT_TYPE_TRANSFORM);
				available_transform_component_ = transform_[i];
			}

			is_transform_components_loaded_ = true;
		}

		void ComponentManager::LoadController() {

			for (int i = 0; i < MAX_SIZE; ++i) {

				controller_[i] = new ControllerComponent();
				controller_[i]->set_id(i);
				controller_[i]->set_next(available_controller_component_);
				controller_[i]->set_component_type(E_COMPONENT_TYPE_TRANSFORM);
				available_controller_component_ = controller_[i];
			}

			is_controller_components_loaded_ = true;
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


		MainComponent* ComponentManager::GetPhysicsComponent(int id) {

			if (!available_physics_component_) {

				ENGINE_ERR_LOG("No Transform Component Available yet");
			} 


			MainComponent* temp = available_physics_component_;
			available_physics_component_ = available_physics_component_->get_next();
			active_physics_component_[id] = temp;
			return temp;

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


		void ComponentManager::Update() {

			UpdatePhysicsComponents();
			UpdateDebugDrawComponent();
			UpdateRenderComponents();
		}

		void ComponentManager::UpdateRenderComponents() {


		}

		void ComponentManager::UpdateTransformComponents() {


		}

		void ComponentManager::UpdatePhysicsComponents() {

			for (auto &itr : active_physics_component_) {

				itr.second->Update();
			}
		}

		void ComponentManager::UpdateControllerComponent() {


		}

		void ComponentManager::UpdateDebugDrawComponent() {


		}



		void ComponentManager::UnloadComponents() {

			Destroy();
		}

		void ComponentManager::RemoveAllActiveComponents() {

			active_render_component_.clear();
			active_physics_component_.clear();
			active_transform_component_.clear();
			active_controller_component_.clear();

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

			if (is_physics_components_loaded_) {

				/*physics components*/
				for (int i = 0; i < MAX_SIZE; i++) {

					delete physics_[i];
				}
				is_physics_components_loaded_ = false;
			}

			if (is_transform_components_loaded_) {

				/*transform_ components*/
				for (int i = 0; i < MAX_SIZE; i++) {

					delete transform_[i];
				}
				is_transform_components_loaded_ = false;
			}


			if (is_controller_components_loaded_) {

				/*transform_ components*/
				for (int i = 0; i < MAX_SIZE; i++) {

					delete controller_[i];
				}
				is_controller_components_loaded_ = false;
			}

			CLEAN_DELETE(ComponentManager::instance_);
		}
	}
}

