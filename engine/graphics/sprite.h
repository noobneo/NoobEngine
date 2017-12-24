#ifndef _SPRITE_H_
#define _SPRITE_H_

/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: sprite.h
Purpose: sprite for rendering
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 16th October 2017
---------------------------------------------------------*/




#include "../maths/vec2.h"
#include "../maths/mat4.h"

#ifdef USE_SDL
#include "../../SDL2.0 Lib/include/SDL_surface.h"
#endif
#include <string>
#include <unordered_map>

namespace enginecore {

	namespace component {

		class BoundingBoxComponent;
		class MainComponent;
	}
}

namespace enginecore {

	namespace graphics {

		class Renderer;
		
		class Sprite 
		{

		public:
			//virtual void Update();
			Sprite();
			Sprite(unsigned char* data, int width, int height , int channels);
			~Sprite();

			void Init();
			void FlipX();
			void FlipY();


			void UpdateProperties(component::MainComponent* boundingbox_);
			void SetPositionX(float position_x);
			void SetPositionY(float position_y);
			void SetPosition(float position_x, float position_y);
			
			inline float get_position_x() { return position_.get_x(); };
			inline float get_position_y() { return position_.get_y(); };

			inline void set_anchorpoint_x(float x) { anchorpoint_.set_x(x); };
			inline void set_anchorpoint_y(float y) { anchorpoint_.set_y(y); };

			void SetSpriteFrame(std::string framename);


			//scale

			void SetScaleX(float scale_x);
			void SetScaleY(float scale_y);
			void SetScale(float scale_x, float scale_y);
			void SetFlip(float flip_x, float flip_y);
			void SetFlipX(float flip_x);
			void SetFlipY(float flip_y);
			void SetZorder(int z_order);


			void set_rotate(float rotate) { rotate_ = rotate; };
			inline int get_z_order() { return z_order_; };
			inline float get_scale_x() { return scale_.get_x(); };
			inline float get_scale_y() { return scale_.get_y(); };

			inline float get_flip_x() { return flip_x_; };
			inline float get_flip_y() { return flip_y_; };

		
			inline void  set_alpha(float alpha) { alpha_ = alpha; };
			inline bool get_active() { return active_; };
			inline void set_active(bool active) { active_ = active; };

			inline void set_width(int width) { width_ = width; };
			inline void set_height(int height) { height_ = height; };


			inline void set_smoothness(float smoothness) { smoothness_ = smoothness; };
			inline int get_width() { return width_ ; };
			inline int get_height() { return height_ ; };

			inline float get_frame_width() { return frame_width_; };
			inline float get_frame_height() { return frame_height_; };

			inline float get_alpha() { return alpha_; };

			inline void set_texture_mode(bool texture_mode) { texture_mode_ = texture_mode; };

			//animation related
			void set_animation_speed(int animation_speed) { animation_speed_ = animation_speed; };
			void set_is_animated_sprite(bool is_animated_sprite) { is_animated_sprite_ = is_animated_sprite; };
			void set_total_frames(int total_frames) { total_frames_ = total_frames; };
			void set_sprite_sheet_rows(int sprite_sheet_rows) { sprite_sheet_rows_ = sprite_sheet_rows; };

			//
			inline void set_name(std::string name) { name_ = name; };
				
			void UpdateSpriteFrames();
			void CreateSpriteMap(std::vector<std::string>);

#ifdef TEST_MODE

			void LeftRotation();
			void RightRotation();
#endif // TEST_MODE


			
#ifdef USE_SDL
			inline SDL_Surface* get_surface() { return surface_; };
			inline SDL_Rect get_bounding_box() { return bounding_box_; };
#endif
			inline void set_is_dirty(bool is_dirty) { is_dirty_ = is_dirty; };
			inline bool get_is_dirty() { return is_dirty_ ; };

		
#ifdef USE_SDL
			inline void set_surface(SDL_Surface* surface) { surface_ = surface; };
#endif
		private:

			void UpdatePosition();
			void Draw();
			void DrawTexture();

		private:	

			bool is_visible_;
			bool is_dirty_;
			bool active_;
			bool is_texture_;

			maths::Vec2 position_;
			maths::Vec2 scale_;
			maths::Mat4 ml_matrix_;
			maths::Vec2 anchorpoint_;

			float rotate_;
			float smoothness_;
			int animation_speed_;					//animation speed (fps)
			int animation_speed_counter_;			
			int width_;								//texture width
			int height_;							//texture height
			float flip_x_;			
			float flip_y_;
			int channels_;
			bool is_animated_sprite_;				//is animated

			unsigned char* data_;
			std::string name_;
#ifdef USE_SDL
			SDL_Rect bounding_box_;
			SDL_Surface* surface_;
#endif // USE_SDL


			unsigned int vao_;
			unsigned int texture_;


			bool is_rect_animation_;
						
			float rect_x_;
			float rect_w_;
			float alpha_;
			int z_order_;
			bool texture_mode_;
			int total_frames_;
			int sprite_sheet_rows_;
			int current_frame_;
			float frame_x_;
			float frame_y_;
			float frame_width_;
			float frame_height_;
			float texture_width_;							// width in texture coords
			float texture_height_;							// height in texture coords

			std::unordered_map<std::string, int> spriteframes_;

			friend class Renderer;
			component::BoundingBoxComponent * bounding_box_;

		
		};

	}
}
#endif // !_SPRITE_H

