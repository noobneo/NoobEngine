#include "manifold.h"

#include "../components/gameobject.h"
#include "../components/bodycomponent.h"
#include "../components/maincomponent.h"

namespace enginecore {

	namespace physics {


		Manifold::Manifold() {
		}


		void Manifold::ApplyImpulse() {


			// Calculate relative velocity
			math::Vector2D relative;

			math::Vector2DSub(&relative, &body2_->get_velocity(), &body1_->get_velocity());


			// Calculate relative velocity in terms of the normal direction
			float velAlongNormal = math::Vector2DDotProduct(&relative, &contacts_.normal);

			// Do not resolve if velocities are separating
			if (velAlongNormal > 0)
				return;

			// Calculate restitution
			float e = 0.0f;// 0.1f;// min(A.restitution, B.restitution)

						   // Calculate impulse scalar
			float j = -(1 + e) * velAlongNormal;
			j /= body1_->get_inverse_mass() + body2_->get_inverse_mass();

			// Apply impulse
			math::Vector2D impulse;

			math::Vector2DScale(&impulse, &contacts_.normal, j);

			math::Vector2D body1_vel;
			math::Vector2D scaled_impulse;
			math::Vector2DScale(&scaled_impulse, &impulse, (body1_->get_inverse_mass()));
			math::Vector2DSub(&body1_vel, &body1_->get_velocity(), &scaled_impulse);
			body1_->set_velocity(body1_vel);

			math::Vector2D body2_vel;
			math::Vector2DScale(&scaled_impulse, &impulse, (body2_->get_inverse_mass()));
			math::Vector2DAdd(&body2_vel, &body2_->get_velocity(), &scaled_impulse);
			body2_->set_velocity(body2_vel);

		}


		void Manifold::PositionCorrection() {
		
		/*	math::Vector2D finalPos;
			math::Vector2DSet(&finalPos, body1_->get_position().x_, body1_->get_position().y_ - contacts_.penetration);
			body1_->set_position(finalPos);

		*/
			/*linear projection*/
	
			const float percent = 0.1f; 
			const float slop = 0.05f; 
			float max_d = contacts_.penetration - slop > 0.0f ? contacts_.penetration - slop : 0.0f;
			//float sum_mass = body1_->get_inverse_mass() + body2_->get_inverse_mass();
			math::Vector2D correction;
			//float scale_factor =  percent * (max_d / sum_mass);
			math::Vector2DScale(&correction, &contacts_.normal, contacts_.penetration);

			math::Vector2D new_body1_pos;
			math::Vector2D scaled_correction;
			math::Vector2DScale(&scaled_correction, &correction, (body1_->get_inverse_mass()));
			math::Vector2DSub(&new_body1_pos, &body1_->get_position(), &scaled_correction);
			body1_->set_position(new_body1_pos);

			math::Vector2D new_body2_pos;
			math::Vector2DScale(&scaled_correction, &correction, (body2_->get_inverse_mass()));
			math::Vector2DAdd(&new_body2_pos, &body2_->get_position(), &scaled_correction);
			body2_->set_position(new_body2_pos);

		}
	}
}