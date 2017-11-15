#include "componentmanager.h"
#include "rendercomponent.h"
#include "bodycomponent.h"
#include "shapecomponent.h"
#include "transformcomponent.h"
#include "controllercomponent.h"
#include "animationcomponent.h"
#include "../common/macros.h"
#include "../enginelogger/enginelogger.h"
#include "gameobject.h"

namespace enginecore {

	namespace component {


		ComponentManager* ComponentManager::instance_ = nullptr;

		ComponentManager::ComponentManager() {

			available_body_component_		= nullptr;
			available_shape_component_		= nullptr;
			available_render_component_		= nullptr;
			available_transform_component_	= nullptr;
			available_controller_component_ = nullptr;
			available_animation_component_	= nullptr;

			is_body_components_loaded_		= false;
			is_shape_components_loaded_		= false;
			is_render_components_loaded_	= false;
			is_transform_components_loaded_ = false;
			is_controller_components_loaded_= false;
			is_animation_components_loaded_ = false;

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

				shape_[i] = new ShapeComponent();
				shape_[i]->set_id(i);
				shape_[i]->set_next(available_shape_component_);
				shape_[i]->set_component_type(E_COMPONENT_TYPE_SHAPE);
				available_shape_component_ = shape_[i];
			}
			is_shape_components_loaded_ = true;


			for (int i = 0; i < MAX_SIZE; ++i) {

				body_[i] = new BodyComponent();
				body_[i]->set_id(i);
				body_[i]->set_next(available_body_component_);
				body_[i]->set_component_type(E_COMPONENT_TYPE_BODY);
				available_body_component_ = body_[i];
			}
			is_body_components_loaded_ = true;
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

		void ComponentManager::LoadAnimation() {

			for (int i = 0; i < MAX_SIZE; ++i) {

				animation_[i] = new AnimationComponent();
				animation_[i]->set_id(i);
				animation_[i]->set_next(available_animation_component_);
				animation_[i]->set_component_type(E_COMPONENT_TYPE_ANIMATION);
				available_animation_component_ = animation_[i];
			}

			is_animation_components_loaded_ = true;
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

		void ComponentManager::Update() {

			UpdateRenderComponents();
			UpdatePhysicsComponents();
			UpdateDebugDrawComponent();
			UpdateAnimationComponent();
		}

		void ComponentManager::UpdateRenderComponents() {

			for (auto &itr : active_render_component_) {

				itr.second->Update();
			}
		}

		void ComponentManager::UpdateTransformComponents() {


		}

		void ComponentManager::UpdatePhysicsComponents() {

		}

		void ComponentManager::UpdateControllerComponent() {


		}

		void ComponentManager::UpdateDebugDrawComponent() {


		}

		void ComponentManager::UpdateAnimationComponent() {

			for (auto &itr : active_animation_component_) {

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

			RemoveAllActiveComponents();
		}


		void ComponentManager::RemoveAllActiveComponents() {

			active_body_component_.clear();
			active_shape_component_.clear();
			active_render_component_.clear();
			active_transform_component_.clear();
			active_controller_component_.clear();
			active_animation_component_.clear();

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

			CLEAN_DELETE(ComponentManager::instance_);
		}
	}
}

