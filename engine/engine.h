#ifndef _ENGINE_H_
#define _ENGINE_H_

/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: engine.h
Purpose: header file for engine
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 14th October 2017
---------------------------------------------------------*/

#include <string>
#include "window\window.h"

 namespace enginecore {

	class Engine
	{
	private:
		Engine();
		~Engine();

		//disable copy constructor and copy assignment constructor
		Engine(const Engine& copy) = delete;
		Engine& operator=(const Engine& copy) = delete;

		void Init();
		void Run();


		//getters
		std::string get_version();

	public:
		
		void ShutDown();
		void Update();
		void Pause();

		static Engine* GetInstance();


		inline bool get_is_paused() { return is_paused_; }

	private:

		int width_;
		int height_;
		
		bool is_paused_;
		bool is_engine_running_;

		std::string window_name_;

		gamewindow::Window* window_;

		static Engine* instance_;
	};
}


#endif