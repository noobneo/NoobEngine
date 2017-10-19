#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "../../external/SDL2.0 Lib/include/SDL.h"

namespace enginecore {

	namespace resourcemanager {

		class Sprite 
		{

		public:
			//virtual void Update();
			

			void SetPositionX(int position_x);
			void SetPositionY(int position_y);
			
			inline int get_position_x() { return position_x_ ; };
			inline int get_position_y() { return position_y_ ; };
			
			inline SDL_Surface* get_surface() { return surface_; };
			inline SDL_Rect get_bounding_box() { return bounding_box_; };

			inline void set_is_dirty(bool is_dirty) { is_dirty_ = is_dirty; };
			inline bool get_is_dirty() { return is_dirty_ ; };

			~Sprite();
		private:

			Sprite();
		

			void UpdatePosition();

			inline void set_surface(SDL_Surface* surface) { surface_ = surface; };

		private:	

			bool is_visible_;
			bool is_dirty_;

			int position_x_;
			int position_y_;

			int width_;
			int height_;

			SDL_Rect bounding_box_;
			SDL_Surface* surface_;
			friend class TextureLoader;
		};

	}
}
#endif // !_SPRITE_H

