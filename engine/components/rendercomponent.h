#ifndef _RENDER_COMPONENT_H_
#define _RENDER_COMPONENT_H_

#include "maincomponent.h"
#include "../maths/vector2D.h"
#include "../resourcemanager/sprite.h"
namespace enginecore {

	namespace component {

		class ComponentManager;

		class RenderComponent : public MainComponent
		{
		public:
			
			void UpdateRenderPosition(math::Vector2D position); 
		private:
			RenderComponent();
			~RenderComponent();

			virtual void Update();
			virtual void Init();

			void set_sprite(resourcemanager::Sprite* image) { image_ = image; };

		private:
			friend class ComponentManager;
			resourcemanager::Sprite* image_;
		};
	}
}

#endif // !_RENDER_COMPONENT_H_
