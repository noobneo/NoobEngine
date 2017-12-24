/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: render.cpp
Purpose: renders the sprite usingOpengL
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 16th October 2017
---------------------------------------------------------*/



#include "renderer.h"
#include "../common/macros.h"
#include "../../SDL2.0 Lib/include/SDL.h"
#include "../graphics/sprite.h"
#include "shader.h"
#include "../enginelogger/enginelogger.h"
#include <algorithm>
#include "../common/scenemanager.h"
#include "../window/window.h"
#include "../particlemanager/particlemanager.h"

namespace enginecore {

	namespace graphics {

		struct Compare {

			bool operator()(Sprite *s, Sprite* s1) {

				return s->get_z_order() < s1->get_z_order();
			}
		};


		Renderer* Renderer::instance_ = nullptr;
		Renderer::Renderer() : window_surface_(nullptr), game_window_(nullptr), shader_(nullptr), shader_texture_(nullptr) ,window_(nullptr), aspect_(0.0f) {

			math::Vector2DSet(&camera_pos_, 0.0f, 0.0f);
			view_ = maths::Mat4(1.0);
			z_order_ = 0;
		}

		Renderer* Renderer::GetInstance() {

			if (!Renderer::instance_) {

				Renderer::instance_ = new Renderer();
			}

			return Renderer::instance_;
		}

		void Renderer::Init() {
#ifdef USE_OPEN_GL

			shader_ = new Shader("engine/shaders/default.vert", "engine/shaders/default.frag");
			shader_->enable();
			
			glViewport(0, 0, window_->get_width(), window_->get_height());

			maths::Mat4 projection_mat = maths::Mat4::Orthographic(0.0f, (float)window_->get_width(), 0.0f, (float)window_->get_height(), 1.0f, 50.0f);

			//maths::Mat4 projection_mat = maths::Mat4::Perspective(80,1, -1.0f, 1.0f);
			ShapeSettings("projection_matrix", projection_mat);
		//	shader_->SetUniformMat4("projection_matrix", projection_mat);
			
			shader_texture_ = new Shader("engine/shaders/default_texture.vert", "engine/shaders/default_texture.frag");
			//shader_texture_->enable();
			TextureSettings("projection_matrix", projection_mat);
		//	shader_texture_->SetUniformMat4("projection_matrix", projection_mat);
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

		//	shader_->enable();

			
#endif // USE_OPEN_GL
		}


		void Renderer::PushToRenderQueue(graphics::Sprite* sprite) {

			sprite->SetZorder(++z_order_);
			sprites_.push_back(sprite);
			SortZ();
		}

		void Renderer::TextureSettings(std::string name , maths::Mat4& mat) {

			shader_texture_->enable();
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			shader_texture_->SetUniformMat4(name.c_str(), mat);
		}

		void Renderer::ShapeSettings(std::string name, maths::Mat4& mat) {

			shader_->enable();
			shader_->SetUniformMat4(name.c_str(), mat);
		}

		void Renderer::TextureMode() {

			shader_texture_->enable();
		}

		void Renderer::ShapeMode() {

			shader_->enable();
		}


		void Renderer::Draw() {

			//	SDL_FillRect(window_surface_, NULL, 0);

			//SDL_MapRGB(window_surface_->format, 0, 0, 0)

#ifdef USE_OPEN_GL
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

#ifdef TEST_MODE

			//DrawImage();

#endif // TEST_MODE

			GLenum error = glGetError();
			if (error != GL_NO_ERROR) {

				ENGINE_ERR_LOG("Opengl Eror while rendering texture %d", error);
			}

			for (auto sprite : sprites_) {

				enginecore::graphics::Sprite* spr = sprite;
				TextureSettings("view_matrix" , view_);
				ShapeSettings("view_matrix", view_);
				spr->Draw();
			}

			ShapeSettings("view_matrix", view_);
			particlesystem::ParticleManager::GetInstance()->RenderParticles();
			particlesystem::ParticleManager::GetInstance()->RemoveInActiveParticles();

			SDL_GL_SwapWindow(game_window_);

			error = glGetError();
			if (error != GL_NO_ERROR) {

				ENGINE_ERR_LOG("Opengl Ereor %d", error);
			}

#else
			SDL_FillRect(window_surface_, NULL, 0);

			for (auto sprite : sprites_) {

				enginecore::graphics::Sprite* spr = sprite;

				SDL_BlitSurface(spr->get_surface(), NULL, window_surface_, &spr->get_bounding_box());

				//spr->set_is_dirty(false);
				//}
			}


			SDL_UpdateWindowSurface(game_window_);
#endif

		}

		void Renderer::StoreGameWindowData(SDL_Window*  game_window, SDL_Surface* window_surface, gamewindow::Window* window) {

			game_window_ = game_window;
			window_surface_ = window_surface;
			window_ = window;
		}

		void Renderer::Reset() {

			for (size_t i = 0; i < sprites_.size(); ) {

				CLEAN_DELETE(sprites_[i]);
				++i;
			}
			z_order_ = 0;

			sprites_.clear();
			math::Vector2DSet(&camera_pos_, 0.0f, 0.0f);
			view_ = maths::Mat4(1.0);
		}

		void Renderer::Destroy() {


			for (size_t i = 0; i < sprites_.size(); ) {

				CLEAN_DELETE(sprites_[i]);
				++i;
			}
			CLEAN_DELETE(Renderer::instance_);
		}

		void Renderer::SortZ() {

			std::sort(sprites_.begin(), sprites_.end(), Compare());
		}
		/*
#ifdef TEST_MODE

		void Renderer::LoadImage() {


		//	shader_->disable();
			shader_texture_ = new Shader("engine/shaders/default_texture.vert", "engine/shaders/default_texture.frag");
	


			float vertices[] = {
				// positions          // colors           // texture coords
				0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
				0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
				-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
				-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
			};
			unsigned int indices[] = {
				0, 1, 2, // first triangle
				2, 3, 0  // second triangle
			};
			
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &EBO);

			glBindVertexArray(VAO);

			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

			// position attribute
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			// color attribute
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);
			// texture coord attribute
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
			glEnableVertexAttribArray(2);
		//	glBindVertexArray(0);

			// load and create a texture 
			// -------------------------
		
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
												   // set the texture wrapping parameters
			glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			// set texture filtering parameters
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			// load image, create texture and generate mipmaps
			int width, height, nrChannels;

			unsigned char *data = stbi_load("playground/resources/globe.jpg", &width, &height, &nrChannels, 0);
			if (data)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				glGenerateMipmap(GL_TEXTURE_2D);
			}
			else
			{
				ENGINE_ERR_LOG("Failed to load image");
			}
			stbi_image_free(data);
			//glEnableVertexAttribArray(0);
			glBindTexture(GL_TEXTURE_2D, 0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}

		void Renderer::DrawImage() {

			if (shader_texture_) {

				//shader_->disable();
				shader_texture_->enable();
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, texture);
				glBindVertexArray(VAO);
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
				glBindTexture(GL_TEXTURE_2D, 0);
				glBindVertexArray(0);
				//shader_1->disable();
				shader_->enable();
			}

		}
#endif // TEST_MODE*/


	}
}