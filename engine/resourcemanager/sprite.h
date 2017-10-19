#ifndef _SPRITE_H
#define _SPRITE_H_

#include "../../external/SDL2.0 Lib/include/SDL.h"

namespace enginecore {

	namespace resourcemanager {

		class Sprite 
		{

		public:

			Sprite();
			~Sprite();

			virtual void Update();
			
			inline void set_position_x(float pos_x) { position_x_ = pos_x; };
			inline void set_position_y(float pos_y) { position_y_ = pos_y; };

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
		};

	}
}
#endif // !_SPRITE_H

