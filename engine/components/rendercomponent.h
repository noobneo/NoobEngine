#ifndef _RENDER_COMPONENT_H_
#define _RENDER_COMPONENT_H_

#include "maincomponent.h"
#include "../maths/vector2D.h"
#include "../graphics/sprite.h"
namespace enginecore {

	namespace component {

		class ComponentManager;
		class ObjectFactory;
		class TransformComponent;

		class RenderComponent : public MainComponent
		{
		public:
			
			void UpdateRenderPosition(math::Vector2D position); 
		private:
			RenderComponent();
			~RenderComponent();

			virtual void Update();
			virtual void Init(GameObject* owner);
			virtual void Reset();

			void set_sprite(graphics::Sprite* image) { image_ = image; };

		private:
			friend class ComponentManager;
			friend class ObjectFactory;

			graphics::Sprite* image_;
			TransformComponent* transform_component_ref_;
		};
	}
}

#endif // !_RENDER_COMPONENT_H_
