#ifndef _RENDERER_H_
#define _RENDERER_H_
#include <vector>
#include "../../SDL2.0 Lib/include/SDL_surface.h"
#include "../../SDL2.0 Lib/include/SDL_video.h"
#include "../graphics/sprite.h"
#include "../common/scenemanager.h"

namespace enginecore {


	namespace graphics {


		class Renderer
		{

		public:

			void Draw();
			void Destroy();

			void PushToRenderQueue(graphics::Sprite* sprite);
			void StoreGameWindowData(SDL_Window*  game_window, SDL_Surface* window_surface);
			static Renderer* GetInstance();
		
		private:
			Renderer() :window_surface_(nullptr), game_window_(nullptr) {}
			~Renderer()=default;

			Renderer& operator=(const Renderer&) = delete;
			Renderer(const Renderer&) = delete;

			void Reset();
		private:
			friend class common::SceneManager;

			static Renderer* instance_;
			std::vector<graphics::Sprite*> sprites_;

			SDL_Surface* window_surface_;
			SDL_Window* game_window_;
		};


	}

}
#endif // !_RENDERER_H_
