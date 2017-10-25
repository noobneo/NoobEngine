#ifndef _RENDERER_H_
#define _RENDERER_H_
#include <vector>
#include "../../SDL2.0 Lib/include/SDL_surface.h"
#include "../../SDL2.0 Lib/include/SDL_video.h"
#include "../resourcemanager/sprite.h"
namespace enginecore {


	namespace renderer {


		class Renderer
		{

		public:

			void Draw();
			void Destroy();

			void PushToRenderQueue(resourcemanager::Sprite* sprite);
			void StoreGameWindowData(SDL_Window*  game_window, SDL_Surface* window_surface);
			static Renderer* GetInstance();
		
		private:
			Renderer() :window_surface_(nullptr), game_window_(nullptr) {}
			~Renderer()=default;

		private:

			static Renderer* instance_;
			std::vector<resourcemanager::Sprite*> sprites_;

			SDL_Surface* window_surface_;
			SDL_Window* game_window_;
		};


	}

}
#endif // !_RENDERER_H_
