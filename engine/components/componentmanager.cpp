#include "componentmanager.h"
#include "rendercomponent.h"
#include "physicscomponent.h"
#include "transformcomponent.h"

#include "../enginelogger/enginelogger.h"

namespace enginecore {

	namespace component {


		ComponentManager::ComponentManager() {

			available_render_component_		= nullptr;
			available_physics_component_	= nullptr;
			available_transform_component_	= nullptr;
			available_controller_component_ = nullptr;
		}

		void ComponentManager::LoadComponents() {

			LoadRender();
			LoadPhyics();
			LoadTransform();
		}


		void ComponentManager::LoadRender() {

			for (int i = 0; i < MAX_SIZE; ++i) {

				render_[i] = new RenderComponent();
				render_[i]->set_id(i);
				render_[i]->set_next(available_render_component_);
				render_[i]->set_component_type(E_COMPONENT_TYPE_RENDER);
				available_render_component_ = render_[i];
			}
		}

		void ComponentManager::LoadPhyics() {

			for (int i = 0; i < MAX_SIZE; ++i) {

				physics_[i] = new PhysicsComponent();
				physics_[i]->set_id(i);
				physics_[i]->set_next(available_physics_component_);
				physics_[i]->set_component_type(E_COMPONENT_TYPE_PHYSICS);
				available_physics_component_ = physics_[i];
			}
		}

		void ComponentManager::LoadTransform() {

			for (int i = 0; i < MAX_SIZE; ++i) {

				transform_[i] = new TransformComponent();
				transform_[i]->set_id(i);
				transform_[i]->set_next(available_transform_component_);
				transform_[i]->set_component_type(E_COMPONENT_TYPE_TRANSFORM);
				available_transform_component_ = transform_[i];
			}
		}

		MainComponent* ComponentManager::GetPhysicsComponent(ComponentType type) {

			if (!available_physics_component_) {

				ENGINE_ERR_LOG("No Transform Component Available yet");
			}
							
			MainComponent* temp = available_physics_component_;
			available_physics_component_ = available_physics_component_->get_next();
			active_physics_component_.push_back(temp);
			return temp;

		}

		MainComponent* ComponentManager::GetRenderComponent(ComponentType type) {

			if (!available_render_component_) {

				ENGINE_ERR_LOG("No Transform Component Available yet");
			}

			MainComponent* temp = available_render_component_;
			available_render_component_ = available_render_component_->get_next();
			active_render_component_.push_back(temp);
			return temp;
		}


		MainComponent* ComponentManager::GetTransformComponent(ComponentType type) {

			if (!available_transform_component_) {

				ENGINE_ERR_LOG("No Transform Component Available yet");
			}

			MainComponent* temp = available_transform_component_;
			available_transform_component_ = available_transform_component_->get_next();
			active_transform_component_.push_back(temp);
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

	}
}

