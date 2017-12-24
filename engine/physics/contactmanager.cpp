#include "contactmanager.h"
#include "../common/macros.h"
#include "../components/shapecomponent.h"
#include "../components/bodycomponent.h"
#include "aabbshape.h"
#include "circleshape.h"
#include "shape.h"
#include "../enginelogger/enginelogger.h"
#include "../event/eventmanager.h"
#include "../event/event.h"
#include <algorithm>

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

			if (manifold.body1_->get_collision_tag() ==  manifold.body2_->get_collision_tag())
				return false;


			AabbShape *A = (AabbShape*)manifold.body1_->get_shape_component()->get_shape();
			AabbShape* B = (AabbShape*)manifold.body2_->get_shape_component()->get_shape();

			// Vector from A to B
#ifdef USE_SDL
			float max_x1 = (A->get_width()) + manifold.body1_->get_position().x_;
			float min_x1 = manifold.body1_->get_position().x_);

			float max_x2 = B->get_width() + manifold.body2_->get_position().x_;
			float min_x2 = manifold.body2_->get_position().x_  ;

			float max_y1 = (A->get_height()) + manifold.body1_->get_position().y_;
			float min_y1 = manifold.body1_->get_position().y_ ;

			float max_y2 = (B->get_height()) + manifold.body2_->get_position().y_;
			float min_y2 = manifold.body2_->get_position().y_;
#else 
			float max_x1 = (A->get_width()*0.5f) + manifold.body1_->get_position().x_;
			float min_x1 = manifold.body1_->get_position().x_ - (A->get_width() *0.5f);

			float max_x2 = (B->get_width() *0.5f) + manifold.body2_->get_position().x_;
			float min_x2 = manifold.body2_->get_position().x_ - (B->get_width() *0.5f);

			float max_y1 = (A->get_height()*0.5f) + manifold.body1_->get_position().y_;
			float min_y1 = manifold.body1_->get_position().y_ - (A->get_height() *0.5f);

			float max_y2 = (B->get_height()*0.5f) + manifold.body2_->get_position().y_;
			float min_y2 = manifold.body2_->get_position().y_ - (B->get_height() * 0.5f);
#endif

			if (max_x1 < min_x2 || min_x1 > max_x2) {

				return false;
			}

			if (max_y1 < min_y2 || min_y1 > max_y2) {

				return false;
			}

			float aw_extent = A->get_width() * 0.5f;// (max_width1 - min_width1 + A->get_width() / 2);
			float ah_extent = A->get_height() * 0.5f;// (max_height1 - min_height1 + );
			float bw_extent = B->get_width() * 0.5f ;// (max_width2 - min_width2 + B->get_width() / 2);
			float bh_extent = B->get_height() * 0.5f;// (max_height2 - min_height2 + B->get_height() / 2);

			math::Vector2D n;
		
#ifdef USE_SDL
			math::Vector2D c1;
			math::Vector2D c2;

		    math::Vector2DSet(&c1, manifold.body1_->get_position().x_+ aw_extent, manifold.body1_->get_position().y_+ ah_extent);
			math::Vector2DSet(&c2, manifold.body2_->get_position().x_+bw_extent, manifold.body2_->get_position().y_+ bh_extent);
			math::Vector2DSub(&n, &manifold.body1_->get_position(), &manifold.body2_->get_position());
#else
		
			math::Vector2DSub(&n, &manifold.body1_->get_position(), &manifold.body2_->get_position());
#endif
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

			return false;//

			if (manifold.body1_->get_type() == E_BODY_TYPE_STATIC && manifold.body2_->get_type() == E_BODY_TYPE_STATIC)
				return false;

			if (manifold.body1_->get_collision_tag() == manifold.body2_->get_collision_tag())
				return false;


			AabbShape *A = (AabbShape*)manifold.body1_->get_shape_component()->get_shape();
			CircleShape* B = (CircleShape*)manifold.body2_->get_shape_component()->get_shape();


			math::Vector2D closest;
			math::Vector2D n;
			math::Vector2DSub(&n, &manifold.body1_->get_position(), &manifold.body2_->get_position());

				// Closest point on A to center of B

				
			math::Vector2DSet(&closest, n.x_, n.y_);
		

			float max_x1 = (A->get_width()*0.5f) + manifold.body1_->get_position().x_;
			float min_x1 = manifold.body1_->get_position().x_ - (A->get_width() *0.5f);

			float max_y1 = (A->get_height()*0.5f) + manifold.body1_->get_position().y_;
			float min_y1 = manifold.body1_->get_position().y_ - (A->get_height() *0.5f);


			float aw_extent = A->get_width() * 0.5f;// (max_width1 - min_width1 + A->get_width() / 2);
			float ah_extent = A->get_height() * 0.5f;// (max_height1 - min_height1 + );


				// Clamp point to edges of the AABB
			closest.x_ = clip(-max_x1, max_x1, closest.x_);
			closest.y_ = clip(-ah_extent, ah_extent, closest.y_);

				bool inside = false;

				// Circle is inside the AABB, so we need to clamp the circle's center
				// to the closest edge
				if (n.x_ == closest.x_ && n.y_ ==closest.y_)
				{
					inside = true;

						// Find closest axis
						if (abs(n.x_) > abs(n.y_))
						{
							// Clamp to closest extent
							if (closest.x_ > 0)
								closest.x_ = aw_extent;
							else
								closest.x_ = -aw_extent;
						}

					// y axis is shorter
						else
						{
							// Clamp to closest extent
							if (closest.y_ > 0)
								closest.y_ = ah_extent;
							else
								closest.y_ = -ah_extent;
						}
				}

				math::Vector2D normal;
				math::Vector2DSub(&normal, &n , &closest);

					float d = math::Vector2DSquareLength(&normal);
					float r = B->get_radius();

				// Early out of the radius is shorter than distance to closest point and
				// Circle not inside the AABB
					if (d > r * r && !inside)
						return false;

					// Avoided sqrt until we needed
					d = sqrt(d);

					// Collision normal needs to be flipped to point outside if circle was
					// inside the AABB
					if (inside)
					{
						
							math::Vector2DSet(&manifold.contacts_.normal, -n.x_, -n.y_);
							manifold.contacts_.penetration = r - d;
					}
					else
					{
						math::Vector2DSet(&manifold.contacts_.normal, n.x_, n.y_);
						manifold.contacts_.penetration = r - d;
					}

					return true;

		}


		bool ContactManager::CircleToCircle(Manifold& manifold) {

			return true;
		}

		bool ContactManager::CircleToAabb(Manifold& manifold) {

		
			return false;
		}


		float ContactManager:: clip(float n, float lower, float upper) {
			return std::max(lower, std::min(n, upper));
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

				events::Event ce;
				ce.set_type(events::E_EVENT_COLLISION);
				ce.set_body1(manifold.body1_);
				ce.set_body2(manifold.body2_);
				events::EventManager::GetInstance()->SendEvent(&ce, manifold.body1_);
				ce.set_body1(manifold.body2_);
				ce.set_body2(manifold.body1_);
				events::EventManager::GetInstance()->SendEvent(&ce, manifold.body2_);

				//manifold.body1_->UpdatePosition();
				//manifold.body2_->UpdatePosition();
			}

		}

	}
}

