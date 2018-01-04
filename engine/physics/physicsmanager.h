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

			/*
			* @function : GetInstance()
			* @return: static reference to the class PhysicsManager
			* @brief: creates and returns the singleton reference to the PhysicsManager
			*/
			static PhysicsManager* GetInstance();

			/*
			* @function : Update()
			* @brief: Updates the bodies and calls for collisioncheck and contact resolution
			*/
			void Update();

			/*
			* @function : Destroy()
			* @brief: deletes the reference to the PhysicsManager
			*/
			void Destroy();


			/*
			* @function : RemoveShape()
			* @brief: Removes and resets the shape from body component
			*/
			void RemoveShape(Shape* shape);
			
			/*
			* @function : GetShape(ShapeType type)
			* @param : type of the shape to be returned
			* @brief: Returns a shape for body.
			*/
			Shape* GetShape(ShapeType type);

			/*
			* @function : AddBodyToUpdateQueue(component::MainComponent* body)
			* @param :body to be addedto queue.
			* @brief: adds body to the update queue of the PhysicsManager
			*/
			void AddBodyToUpdateQueue(component::MainComponent* body);

			//inline void set_gravity(float gravity) { gravity_ = gravity;};
			inline float get_gravity() { return gravity_; };

		private:
			//ctor
			PhysicsManager();
			PhysicsManager(const PhysicsManager&) = delete;
			PhysicsManager& operator=(const PhysicsManager&) = delete;

			//dtor
			~PhysicsManager() = default;
			
			
			/*
			* @function : LoadShapes()
			* @brief: Creates and loads all the shapes.
			*/
			void LoadShapes();

			/*
			* @function : DestroyShapes()
			* @brief: it destroys all the shapes created.
			*/
			void DestroyShapes();


			/*
			* @function : Reset()
			* @brief: cleats the body update queue.
			*/
			void Reset();

			//returns shape
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
