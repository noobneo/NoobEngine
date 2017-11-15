#include "renderer.h"
#include "../common/macros.h"

#include "../../SDL2.0 Lib/include/SDL.h"
#include "../graphics/sprite.h"

#ifdef TEST_MODE
#include "../enginelogger/enginelogger.h"
#endif // TEST_MODE

namespace enginecore {

	namespace graphics {

		Renderer* Renderer::instance_ = nullptr;

		Renderer* Renderer::GetInstance() {

			if (!Renderer::instance_) {

				Renderer::instance_ = new Renderer();
			}

			return Renderer::instance_;
		}

		void Renderer::PushToRenderQueue(graphics::Sprite* sprite) {

			sprites_.push_back(sprite);
		}

		void Renderer::Draw() {

			SDL_FillRect(window_surface_, NULL, 0);//SDL_MapRGB(window_surface_->format, 0, 0, 0)

			for (auto sprite : sprites_) {

				enginecore::graphics::Sprite* spr = sprite;
				//if (spr->get_is_dirty()) {

				SDL_BlitSurface(spr->get_surface(),NULL,window_surface_,&spr->get_bounding_box());
					//spr->set_is_dirty(false);
				//}
			}

			SDL_UpdateWindowSurface(game_window_);
		}

		void Renderer::StoreGameWindowData(SDL_Window*  game_window, SDL_Surface* window_surface) {

			game_window_ = game_window;
			window_surface_ = window_surface;

		}

		void Renderer:: Reset() {

			for (size_t i = 0; i < sprites_.size(); ) {

				CLEAN_DELETE(sprites_[i]);
				++i;
			}

			sprites_.clear();
		}

		void Renderer::Destroy() {

			#ifdef TEST_MODE
				ENGINE_LOG("DEstroying the Renderer ");
			#endif // TEST_MODE


			for (size_t i = 0; i < sprites_.size(); ) {

				CLEAN_DELETE(sprites_[i]);
				++i;
			}
			CLEAN_DELETE(Renderer::instance_);
		}

	}
}