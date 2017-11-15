#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "../../SDL2.0 Lib/include/SDL_surface.h"


namespace enginecore {

	namespace graphics {

		class Sprite 
		{

		public:
			//virtual void Update();
			

			void SetPositionX(float position_x);
			void SetPositionY(float position_y);
			void SetPosition(float position_x, float position_y);
			
			inline float get_position_x() { return position_x_ ; };
			inline float get_position_y() { return position_y_ ; };
			
			inline SDL_Surface* get_surface() { return surface_; };
			inline SDL_Rect get_bounding_box() { return bounding_box_; };

			inline void set_is_dirty(bool is_dirty) { is_dirty_ = is_dirty; };
			inline bool get_is_dirty() { return is_dirty_ ; };

			Sprite();
			~Sprite();
			inline void set_surface(SDL_Surface* surface) { surface_ = surface; };
		private:

		

			void UpdatePosition();


		private:	

			bool is_visible_;
			bool is_dirty_;

			float position_x_;
			float position_y_;

			int width_;
			int height_;

			SDL_Rect bounding_box_;
			SDL_Surface* surface_;
			//friend class resourcemanager::TextureLoader;
		};

	}
}
#endif // !_SPRITE_H

