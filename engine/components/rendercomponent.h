#ifndef _RENDER_COMPONENT_H_
#define _RENDER_COMPONENT_H_


/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: rendercomponent.h
Purpose: renders component for the gameobjects
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 16th October 2017
---------------------------------------------------------*/



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
			//void SetSize(float width , float height);
			void SetFlip(float flip_x, float flip_y);

			virtual void UpdateProperties();
			
			inline float  get_flip_y() { return image_->get_flip_y(); };
			inline float get_flip_x() { return image_->get_flip_x(); };

			inline int  get_width() { return image_->get_width(); };
			inline int get_height() { return image_->get_height(); };

			inline void FlipX() { image_->FlipX(); };
			inline void FlipY() { image_->FlipY(); };

			inline void set_flip_x(float flip_x) { image_->SetFlipX(flip_x); };
			inline void set_flip_y(float flip_y) { image_->SetFlipY(flip_y); };

			inline void SetScaleX(float scale_x) { image_->SetScaleX(scale_x); };
			inline void SetScaleY(float scale_y) { image_->SetScaleY(scale_y); };


			 void SetBlink(bool blink);

			void SetRotation(float rotate);

			virtual void set_active(bool);
		private:
			RenderComponent();
			~RenderComponent();

			virtual void Update();
			virtual void Reset();
			virtual void HandleEvent(events::Event *event) ;
			virtual void Init(GameObject* owner);

			void set_sprite(graphics::Sprite* image) { image_ = image; };


#ifdef TEST_MODE
			public:
				void LeftRotate();
				void RightRotate();
#endif // TEST_MODE

		private:
			friend class ComponentManager;
			friend class ObjectFactory;

			graphics::Sprite* image_;
			float previous_alpha_;
			TransformComponent* transform_component_ref_;
		};
	}
}

#endif // !_RENDER_COMPONENT_H_
