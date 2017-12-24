#ifndef _PHYSICS_MANAGER_H_
#define _PHYSICS_MANAGER_H_

#include <unordered_map>
#include "../game-global.h"
#include "shape.h"
#include "../components/maincomponent.h"
#include "../common/scenemanager.h"

namespace enginecore {

	namespace physics {

		class ContactManager;

		class PhysicsManager
		{

		public:
			static PhysicsManager* GetInstance();
			void Update();
			void Destroy();

			void RemoveShape(Shape* shape);
			Shape* GetShape(ShapeType type);

			void AddBodyToUpdateQueue(component::MainComponent* body);

			//inline void set_gravity(float gravity) { gravity_ = gravity;};
			inline float get_gravity() { return gravity_; };

		private:
			PhysicsManager();
			~PhysicsManager() = default;
			PhysicsManager(const PhysicsManager&) = delete;
			PhysicsManager& operator=(const PhysicsManager&) = delete;

			void LoadShapes();
			void DestroyShapes();
			void Reset();

			Shape* GetCircleShape();
			Shape* GetAabbShape();
		private:
			friend class common::SceneManager;

			static PhysicsManager* instance_;
			float gravity_;

			Shape* aabb_pool_[MAX_SIZE];
			Shape* circle_pool_[MAX_SIZE];

			Shape* available_shape_aabb_;
			Shape* available_shape_circle_;

			ContactManager* contact_manager_;

			std::unordered_map<int, component::MainComponent*> bodies_;
			
		};

	}
}

#endif // !_PHYSICS_MANAGER_H_
