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
			ContactManager();
			~ContactManager() = default;

			void ResetContactList();
			void CheckForCollision(component::BodyComponent* shape1 , math::Vector2D position1 , component::BodyComponent* shape2, math::Vector2D position2);


			//function call backs
			bool AabbToAabb(Manifold& manifold);
			bool AabbToCircle(Manifold& manifold);
			bool CircleToCircle(Manifold& manifold);
			bool CircleToAabb(Manifold& manifold);


			void ResolveContancts();
			void PositionCorrection();

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
