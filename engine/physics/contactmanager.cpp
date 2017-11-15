#include "contactmanager.h"
#include "../common/macros.h"
#include "../components/shapecomponent.h"
#include "../components/bodycomponent.h"
#include "aabbshape.h"
#include "shape.h"
#include "../enginelogger/enginelogger.h"

namespace enginecore {

	namespace physics {


		ContactManager::ContactManager(){

			function_array_[E_SHAPE_AABB][E_SHAPE_AABB] = FUNCTION_CALLBACK(ContactManager::AabbToAabb, this);
			function_array_[E_SHAPE_AABB][E_SHAPE_CIRCLE] = FUNCTION_CALLBACK(ContactManager::AabbToCircle, this);
			function_array_[E_SHAPE_CIRCLE][E_SHAPE_CIRCLE] = FUNCTION_CALLBACK(ContactManager::CircleToCircle, this);
			function_array_[E_SHAPE_CIRCLE][E_SHAPE_AABB] = FUNCTION_CALLBACK(ContactManager::CircleToAabb, this);

		}


		bool ContactManager::AabbToAabb(Manifold& manifold) {


			if (manifold.body1_->get_type() == E_BODY_TYPE_STATIC && manifold.body2_->get_type() == E_BODY_TYPE_STATIC)
				return false;


			AabbShape *A = (AabbShape*)manifold.body1_->get_shape_component()->get_shape();
			AabbShape* B = (AabbShape*)manifold.body2_->get_shape_component()->get_shape();

			// Vector from A to B

			float max_width1 = A->get_width() + manifold.body1_->get_position().x_;
			float min_width1 = manifold.body1_->get_position().x_;
			float max_width2 = B->get_width() + manifold.body2_->get_position().x_;
			float min_width2 = manifold.body2_->get_position().x_ ;

			float max_height1 = A->get_height() + manifold.body1_->get_position().y_;
			float min_height1 = manifold.body1_->get_position().y_ ;
			float max_height2 = B->get_height() + manifold.body2_->get_position().y_;
			float min_height2 = manifold.body2_->get_position().y_ ;


			if (max_width1 < min_width2 || min_width1 > max_width2) {

				return false;
			}

			if (max_height1 < min_height2 || min_height1 > max_height2) {

				return false;
			}

			float aw_extent = A->get_width() * 0.5f;// (max_width1 - min_width1 + A->get_width() / 2);
			float bw_extent = B->get_width() * 0.5f ;// (max_width2 - min_width2 + B->get_width() / 2);
			float ah_extent = A->get_height() * 0.5f;// (max_height1 - min_height1 + );
			float bh_extent = B->get_height() * 0.5f;// (max_height2 - min_height2 + B->get_height() / 2);

			math::Vector2D n;
			math::Vector2D c1;
			math::Vector2D c2;

			math::Vector2DSet(&c1, min_width1 + aw_extent, min_height1 + ah_extent);
			math::Vector2DSet(&c2, min_width2 + bw_extent, min_height2 + bh_extent);

			math::Vector2DSub(&n, &c1, &c2);
		//	ENGINE_LOG("Collision");

			// Calculate half extents along x axis for each object

			// Calculate overlap on x axis
			float x_overlap = aw_extent + bw_extent - abs(n.x_);

			// SAT test on x axis
			if (x_overlap > 0)
			{

				// Calculate  extents along x axis for each object

					// Calculate overlap on y axis
				float y_overlap = ah_extent + bh_extent - abs(n.y_);

					// SAT test on y axis
					if (y_overlap > 0)
					{
						// Find out which axis is axis of least penetration
						if (x_overlap < y_overlap)
						{
							// Point towards B knowing that n points from A to B
							if (n.x_ < 0)
								math::Vector2DSet(&manifold.contacts_.normal, 1.0, 0.0);
							else
								math::Vector2DSet(&manifold.contacts_.normal, -1.0, 0.0);

							manifold.contacts_.penetration = x_overlap;

							/*math::Vector2D contactPoint;
							math::Vector2DSet(&contactPoint, manifold.body2_->get_position().x_, manifold.body1_->get_position().y_);
							math::Vector2D normal;
							float distance = fabs(math::Vector2DDistance(&contactPoint, &manifold.body1_->get_position()));
							manifold.contacts_.penetration = A->get_width() - distance;*/

							return true;
						}
						else
						{
							// Point toward B knowing that n points from A to B

							if (n.y_ < 0)
								math::Vector2DSet(&manifold.contacts_.normal, 0.0, 1.0);
							else
								math::Vector2DSet(&manifold.contacts_.normal, 0.0, -1.0);

						/*	math::Vector2D contactPoint;
							math::Vector2DSet(&contactPoint, manifold.body1_->get_position().x_, manifold.body2_->get_position().y_);
							math::Vector2D normal;
							float distance = fabs(math::Vector2DDistance(&contactPoint, &manifold.body1_->get_position()));
							//ENGINE_LOG("y penetration x: %.2f , y: %.2f", contactPoint.x_ , contactPoint.y_);
							//ENGINE_LOG("Body position x: %.2f", A->get_height() - distance);
							manifold.contacts_.penetration = A->get_height() - distance;*/

							manifold.contacts_.penetration = y_overlap;
							return true;
						}
					}
			}

			return false;
		}


		bool ContactManager::AabbToCircle(Manifold& manifold) {


			return false;
		}


		bool ContactManager::CircleToCircle(Manifold& manifold) {

			return true;
		}

		bool ContactManager::CircleToAabb(Manifold& manifold) {

			Manifold temp;
			return false;
		}


		void ContactManager::ResetContactList() {

			contacts_.clear();

		}

		void ContactManager::CheckForCollision(component::BodyComponent* body1, math::Vector2D position1, component::BodyComponent* body2, math::Vector2D position2) {

			Manifold m;
			ShapeType type1 = (static_cast<component::ShapeComponent*>( body1->get_shape_component()))->get_shape_type();
			ShapeType type2 = (static_cast<component::ShapeComponent*>(body2->get_shape_component()))->get_shape_type();

			m.body1_ = body1;
			m.body2_ = body2;

			if (function_array_[type1][type2](m)) {

				contacts_.push_back(m);
			}
		}


		void ContactManager::ResolveContancts()
		{

			for (auto &manifold : contacts_) {

				manifold.ApplyImpulse();
				//manifold.body1_->UpdatePosition();
				//manifold.body2_->UpdatePosition();
			}

		}


		void ContactManager::PositionCorrection()
		{

			for (auto &manifold : contacts_) {

				manifold.PositionCorrection();
				//manifold.body1_->UpdatePosition();
				//manifold.body2_->UpdatePosition();
			}

		}

	}
}

