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
#include "../../external/SDL2.0 Lib/include/SDL.h"

namespace enginecore {

	namespace gamewindow {

		class Window
		{
		public:
			Window() :width_(800), height_(800), window_name_("") , game_window_(nullptr){}
			Window(int width , int height , std::string window_name, SDL_Window* game_window = nullptr) :width_(width), height_(height), window_name_(window_name), game_window_(nullptr) {}
			~Window();
			
			bool CreateWindow();
		private:

			Window(const Window &) = delete;
			Window& operator=(const Window&) = delete;

		private:

			int width_;
			int height_;

			std::string window_name_;

			SDL_Window * game_window_;

		};
	}//namespace gamewindow
}//namespace enginecore



#endif // ! 



