#ifndef _RENDERER_H_
#define _RENDERER_H_

/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: render.h
Purpose: renders the sprite usingOpengL
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 16th October 2017
---------------------------------------------------------*/





#include <vector>
#include "../../SDL2.0 Lib/include/SDL_surface.h"
#include "../../SDL2.0 Lib/include/SDL_video.h"

#include "../maths/mat4.h"
#include "../maths/vector2D.h"

namespace enginecore {
	namespace gamewindow {

		class Window;
	}
}

namespace enginecore {

	namespace common {

		class SceneManager;
	}
}

namespace enginecore {


	namespace graphics {

		class Shader;
		class Sprite;
		
		class Renderer
		{

		public:

			void Draw();
			void Destroy();
			void Init();

			void TextureSettings(std::string , maths::Mat4&);
			void ShapeSettings(std::string, maths::Mat4&);

			void TextureMode();
			void ShapeMode();

			void SortZ();
			void PushToRenderQueue(graphics::Sprite* sprite);
			void StoreGameWindowData(SDL_Window*  game_window, SDL_Surface* window_surface, gamewindow::Window* window_);
			static Renderer* GetInstance();
		
			inline Shader* get_shader() { return shader_; };
			inline Shader* get_shader_texture() { return shader_texture_; };
			inline void set_view(maths::Mat4& view) { view_ = view; };

			inline void set_camera_pos(math::Vector2D& camera_pos) { camera_pos_ = camera_pos; };
			inline math::Vector2D& get_camera_pos() { return camera_pos_ ; };

		private:
			Renderer();
			~Renderer()=default;

			Renderer& operator=(const Renderer&) = delete;
			Renderer(const Renderer&) = delete;


			void Reset();
			
		private:
			friend class common::SceneManager;

			static Renderer* instance_;
			std::vector<Sprite*> sprites_;

			SDL_Surface* window_surface_;
			SDL_Window* game_window_;
			Shader *shader_;
			Shader *shader_texture_;

#ifdef TEST_MODE

			

#endif // TEST_MODE
			int z_order_;
			gamewindow::Window* window_;
			float aspect_;
			maths::Mat4 view_;
			math::Vector2D camera_pos_;
		};
	}

}
#endif // !_RENDERER_H_
