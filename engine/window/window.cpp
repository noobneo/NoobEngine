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

namespace enginecore {

	namespace gamewindow {

		Window::~Window(){

			ENGINE_LOG("Destroying the window");
			// Close and destroy the window
			SDL_DestroyWindow(game_window_);

			ENGINE_LOG("quiting the sdl");
			// Quit SDL subsystems
			SDL_Quit();
		}


		bool Window::CreateWindow() {

			int error = 0;
			if ((error = SDL_Init(SDL_INIT_VIDEO)) < 0)
			{
				ENGINE_ERR_LOG("Couldn't initialize SDL, error %i\n", error);
				return false;
			}


			game_window_ = SDL_CreateWindow(window_name_.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width_, height_, SDL_WINDOW_SHOWN);
			
			if (!game_window_) {

				ENGINE_ERR_LOG("Could not create window");
				return false;
			}

			window_surface_ = SDL_GetWindowSurface(game_window_);
			return true;
		}

		void Window::SetWindowName(std::string window_name) {

			window_name_ = "NoobEngine 0.1v  dt: "+window_name;

			SDL_SetWindowTitle(game_window_, window_name_.c_str());
		}
	}
}
