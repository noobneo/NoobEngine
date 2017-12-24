/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: window.cpp
Purpose: contains method implementation of class window
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 16th October 2017
---------------------------------------------------------*/


#include "window.h"
#include "../enginelogger/enginelogger.h"
#include "../../external/SDL2.0 Lib/include/SDL.h"
#include "GL\glew.h"

namespace enginecore {

	namespace gamewindow {

		Window::~Window(){

			ENGINE_LOG("Destroying the window");
			// Close and destroy the window
			SDL_DestroyWindow(game_window_);

			SDL_GL_DeleteContext(opengl_context_);

			ENGINE_LOG("quiting the sdl");
			// Quit SDL subsystems
			SDL_Quit();
		}


		bool Window::CreateWindow() {

			int error = 0;
			if ((error = SDL_Init(SDL_INIT_VIDEO )) < 0)
			{
				ENGINE_ERR_LOG("Couldn't initialize SDL, error %i\n", error);
				return false;
			}

			//SDL_GL_LoadLibrary(NULL); // Default OpenGL is fine.

			//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
			//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);


		//	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
			// Also request a depth buffer
		//	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		//	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

			game_window_ = SDL_CreateWindow(window_name_.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width_, height_, SDL_WINDOW_SHOWN| SDL_WINDOW_OPENGL);
			
			if (!game_window_) {

				ENGINE_ERR_LOG("Could not create window");
				return false;
			}


				//Create context
			opengl_context_ = SDL_GL_CreateContext(game_window_);

			SDL_GL_MakeCurrent(game_window_, opengl_context_);

			if (opengl_context_ == NULL)	{
				char *version  = (char *) glGetString(GL_VERSION);
				ENGINE_ERR_LOG("OpenGL version %s", version);
				ENGINE_ERR_LOG("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
				return false;
			}

			SDL_GL_SetSwapInterval(1);

			window_surface_ = SDL_GetWindowSurface(game_window_);

			if (glewInit() != GLEW_OK) {

				ENGINE_ERR_LOG("Error initialising GLEW");
			}

			return true;
		}

		void Window::SetWindowName(std::string window_name) {

				std::string name = window_name_;
				name = name+ " dt: "+ window_name;

				SDL_SetWindowTitle(game_window_, name.c_str());
		}
	}
}
