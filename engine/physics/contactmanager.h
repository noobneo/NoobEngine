#ifndef _CONTACT_MANAGER_H_
#define _CONTACT_MANAGER_H_ 

#include "manifold.h"
#include <vector>
#include "../maths/vector2D.h"
#include "../enums.h"
#include <functional>
#include "../components/bodycomponent.h"

namespace enginecore{

	namespace physics {

		class PhysicsManager;
		class Shape;
		class Event;

		class ContactManager
		{
		private:
			//ctor
			ContactManager();
			
			//dtor
			~ContactManager() = default;

			/*
			* @function : ResetContactList()
			* @brief: Resets the contact list created in the previous loop
			*/
			void ResetContactList();
			
			/*
			* @function : CheckForCollision(component::BodyComponent* shape1 , math::Vector2D position1 , component::BodyComponent* shape2, math::Vector2D position2)
			* @param shape1: shape1 of the collision checking
			* @param shape2 : shape2 for the collision checking
			* @param position1 : position of the body1
			* @param position1 : position of the body2
			* @brief: Checks collision between two given bodies and stores them in contact list if collsion occurs
			*/
			void CheckForCollision(component::BodyComponent* shape1 , math::Vector2D position1 , component::BodyComponent* shape2, math::Vector2D position2);


			/*
			* @function : AabbToAabb(Manifold& manifold)
			* &param : manifold stores the contact information
			* @return: bool for the collision status
			* @brief: Checks and returns the collision status between 2 Aabb. 
			* it also stores the contact information in Manifold.
			*/
			bool AabbToAabb(Manifold& manifold);

			/*
			* @function : AabbToCircle(Manifold& manifold)
			* &param : manifold stores the contact information
			* @return: bool for the collision status
			* @brief: Checks and returns the collision status between Aabb and circle.
			* it also stores the contact information in Manifold.
			*/
			bool AabbToCircle(Manifold& manifold);
			
			//not implmented yet
			bool CircleToCircle(Manifold& manifold);
			bool CircleToAabb(Manifold& manifold);


			/*
			* @function : ResolveContancts()
			* @brief: It resolves the contacts between two bodies
			*/
			void ResolveContancts();
			
			/*
			* @function : PositionCorrection()
			* @brief: This method peforms position correction on touch bodies to avoid
			* merging of bodies
 			*/
			void PositionCorrection();

			/*
			* @function : clip(float n, float lower, float upper)
			* @return: returns float which is the clipped value
			* @brief: clips the value between the given range
			*/
			float clip(float n, float lower, float upper);
			//CheckForCollisions();// checks for collision
		private:
			friend class PhysicsManager;

			std::vector<Manifold> contacts_;
			std::function<bool(Manifold & manifold)> function_array_[E_TOTAL_SHAPES][E_TOTAL_SHAPES];
		};

	}
}

#endif // !_CONTACT_MANAGER_H_
