#include "physicsmanager.h"

#include "../enginelogger/enginelogger.h"
#include "../common/macros.h"

#include "../components/bodycomponent.h"

#include "aabbshape.h"
#include "circleshape.h"

#include "contactmanager.h"	

#include "../fpscontroller/fpscontroller.h"

#include "../components/gameobject.h"
namespace enginecore {

	namespace physics {

		PhysicsManager* PhysicsManager::instance_ = nullptr;

		PhysicsManager::PhysicsManager() {

			gravity_ =  enginecore::EngineConfig::config_->gravity_ * enginecore::EngineConfig::config_->ptm_;
			bodies_.clear();
			available_shape_aabb_ = nullptr;
			available_shape_circle_ = nullptr;
			contact_manager_ = new ContactManager();
			LoadShapes();
		}

		PhysicsManager* PhysicsManager::GetInstance() {

			if (!PhysicsManager::instance_) {

				PhysicsManager::instance_ = new PhysicsManager();

			}

			return PhysicsManager::instance_;

		}


		Shape* PhysicsManager::GetShape(ShapeType type) {

			Shape* shape;
			if (type == E_SHAPE_AABB) {

				shape = GetAabbShape();
			}
			else {

				shape= GetCircleShape();
			}

			return shape;
		}

		void PhysicsManager:: AddBodyToUpdateQueue(component::MainComponent* body) {

			auto it = bodies_.find(body->get_id());

			if (it != bodies_.end()) {

				ENGINE_ERR_LOG("Body is alread added!");
				return;
			}

			bodies_[body->get_id()] = body;

		}

		void PhysicsManager::LoadShapes() {

			for (int i = 0; i < MAX_SIZE; i++) {

				aabb_pool_[i] = new AabbShape(E_SHAPE_AABB);
				aabb_pool_[i]->set_next(available_shape_aabb_);
				aabb_pool_[i]->set_id(i);
				available_shape_aabb_ = aabb_pool_[i];
			}

			for (int i = 0; i < MAX_SIZE; i++) {

				circle_pool_[i] = new CircleShape(E_SHAPE_CIRCLE);
				circle_pool_[i]->set_next(available_shape_circle_);
				circle_pool_[i]->set_id(i);
				available_shape_circle_ = circle_pool_[i];
			}

		}

		Shape* PhysicsManager::GetCircleShape() {

			if (!available_shape_circle_) {

				ENGINE_ERR_LOG("No circle shapes availble now!");
				return nullptr;
			}

			Shape* temp = available_shape_circle_;
			available_shape_circle_ = temp->get_next();
			return temp;
		}

		Shape* PhysicsManager::GetAabbShape() {

			if (!available_shape_aabb_) {

				ENGINE_ERR_LOG("No AABB shapes availble now!");
				return nullptr;
			}

			Shape* temp = available_shape_aabb_;
			available_shape_aabb_ = temp->get_next();
			return temp;
		}

		void PhysicsManager::RemoveShape(Shape* shape) {

			shape->Reset();
			if (shape->get_type() == E_SHAPE_AABB) {

				shape->set_next(available_shape_aabb_);
				available_shape_aabb_ = shape;
			}
			else {

				shape->set_next(available_shape_circle_);
				available_shape_circle_ = shape;
			}
		}

		void PhysicsManager::Update() {


			//integerate

			for (auto &it : bodies_) {

				component::BodyComponent* body_component = static_cast<component::BodyComponent*>(it.second);
				body_component->Integerate(fps::FpsController::GetInstance()->get_dt());
			}

			//clear contact list
			contact_manager_->ResetContactList();

			//check for contacts
			for (auto &it1 : bodies_) {

				for (auto &it2 : bodies_) {

					component::BodyComponent* body_component1 = static_cast<component::BodyComponent*>(it1.second);
					component::BodyComponent* body_component2 = static_cast<component::BodyComponent*>(it2.second);

					
					
					if (body_component1->get_id() != body_component2->get_id() && body_component1->get_active() & body_component2->get_active() && (!(body_component2->get_is_bullet() & body_component1->get_is_bullet()))) {

						contact_manager_->CheckForCollision(body_component1, body_component1->get_position(), body_component2, body_component2->get_position());
					}
				}
			}


			//resolve contacts
			contact_manager_->ResolveContancts();
			contact_manager_->PositionCorrection();
			//contact_manager_->CallOnCollision();

			//update position
			for (auto &it : bodies_) {

				component::BodyComponent* body_component = static_cast<component::BodyComponent*>(it.second);
				if (body_component->get_is_physics_on()) {
					body_component->UpdatePosition();
				}
			}
		}


		void PhysicsManager::DestroyShapes() {

			for (int i = 0; i < MAX_SIZE; i++) {

				delete aabb_pool_[i];
			}

			for (int i = 0; i < MAX_SIZE; i++) {

				delete circle_pool_[i];
			}
		}


		void PhysicsManager::Reset() {

			bodies_.clear();
		}

		void PhysicsManager::Destroy() {

#ifdef TEST_MODE
			ENGINE_LOG("Destroying the Physics Manager");
#endif // TEST_MODE

			DestroyShapes();

			delete contact_manager_;
			CLEAN_DELETE(PhysicsManager::instance_);
		}

	}
}

