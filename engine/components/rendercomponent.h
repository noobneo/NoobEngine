#ifndef _RENDER_COMPONENT_H_
#define _RENDER_COMPONENT_H_

#include "maincomponent.h"
#include "../maths/vector2D.h"
#include "../resourcemanager/sprite.h"
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

			void set_sprite(resourcemanager::Sprite* image) { image_ = image; };

		private:
			friend class ComponentManager;
			friend class ObjectFactory;

			resourcemanager::Sprite* image_;
			TransformComponent* transform_component_ref_;
		};
	}
}

#endif // !_RENDER_COMPONENT_H_
