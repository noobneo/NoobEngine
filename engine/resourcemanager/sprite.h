#ifndef _SPRITE_H
#define _SPRITE_H_

#include "../../external/SDL2.0 Lib/include/SDL.h"

namespace enginecore {

	namespace resourcemanager {

		class Sprite 
		{

		public:
			//virtual void Update();
			
			inline void set_position_x(float pos_x) { position_x_ = pos_x; };
			inline void set_position_y(float pos_y) { position_y_ = pos_y; };

		private:

			Sprite();
			~Sprite();

			void UpdatePosition();

			inline void set_surface(SDL_Surface* surface) { surface_ = surface; };

		private:	

			bool is_visible_;
			bool is_dirty_;

			float position_x_;
			float position_y_;

			int width_;
			int height_;

			SDL_Rect bounding_box_;
			SDL_Surface* surface_;
			friend class TextureLoader;
		};

	}
}
#endif // !_SPRITE_H

