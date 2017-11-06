#ifndef _ANIMATION_COMPONENT_H_
#define _ANIMATION_COMPONENT_H_

#include "maincomponent.h"
#include "../maths/vector2D.h"
#include <string>
namespace enginecore {

	namespace component {

		class ComponentManager;
		class ObjectFactory;

		class AnimationComponent : public MainComponent
		{

		private:
			virtual void Update();
			virtual void Init(GameObject* owner);

			AnimationComponent();
			~AnimationComponent();
			AnimationComponent(const AnimationComponent&) = delete;
			AnimationComponent& operator=(const AnimationComponent&) = delete;

			void set_limit(float limit) { limit_ = limit; };
			void set_step(float step) { step_ = step; };
			void set_direction(std::string  direction) { direction_ = direction; };

 
		private:
			friend class ComponentManager;
			friend class ObjectFactory;

			std::string direction_;
			float current_step_;
			float limit_;
			float step_;
			int dir_;
			
		};

	}
}

#endif // _ANIMATION_COMPONENT_H_
