#ifndef _WINDOW_H
#define _WINDOW_H

/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: window.h
Purpose: creates a game window 
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 16th October 2017
---------------------------------------------------------*/



#include<string>
#include "../../external/SDL2.0 Lib/include/SDL_video.h"

namespace enginecore {

	namespace gamewindow {

		class Window
		{
		public:
			Window() :width_(800), height_(800), window_name_("") , game_window_(nullptr), window_surface_(nullptr){}
			Window(int width , int height , std::string window_name, SDL_Window* game_window = nullptr , SDL_Surface* window_surface = nullptr) :width_(width), height_(height), window_name_(window_name), 
																																					game_window_(nullptr), window_surface_(nullptr){}
			~Window();
			
			bool CreateWindow();

			void SetWindowName(std::string window_name);

			inline SDL_Surface* get_window_surface() { return window_surface_; };
			inline SDL_Window*	get_game_window() { return game_window_; };


			inline int get_width() { return width_; };
			inline int get_height() { return height_; };

		private:

			Window(const Window &) = delete;
			Window& operator=(const Window&) = delete;

		private:

			int width_;
			int height_;

			std::string window_name_;

			SDL_Window * game_window_;
			SDL_Surface* window_surface_;
			SDL_GLContext opengl_context_;


		};
	}//namespace gamewindow
}//namespace enginecore



#endif // ! 



