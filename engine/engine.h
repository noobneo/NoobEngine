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

#include "components\gameobject.h"

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
		void ShutDown();
		void Update();
		void Pause();

		void InstantiateModules();

	public: 
		

		static Engine* GetInstance();
		void Run();

		/*setters*/
		inline void set_is_running(bool is_engine_running) { is_engine_running_ = is_engine_running; }


		/*getters*/
		inline bool get_is_paused() { return is_paused_; }
		inline std::string Engine::get_version() { return "NoobEngine 0.1v";}

	private:

		int width_;
		int height_;
		
		bool is_paused_;
		bool is_engine_running_;

		std::string window_name_;

		gamewindow::Window* window_;

		static Engine* instance_;


#ifdef TEST_MODE

		component::GameObject* obj_;
#endif
	};
}


#endif