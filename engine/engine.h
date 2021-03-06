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
		//ctor
		Engine();
		//dtor
		~Engine();

		//disable copy constructor and copy assignment constructor
		Engine(const Engine& copy) = delete;
		Engine& operator=(const Engine& copy) = delete;


		/*
		* @function : Init()
		* @brief: Creates a singleton reference to SceneManager and returns it
		*/
		void Init();

		/*
		* @function : ShutDown()
		* @brief: Shuts down the engine
		*/
		void ShutDown();

		/*
		* @function : Update()
		* @brief:Updates the engine and all the modules
		*/
		void Update();

		/*
		* @function : ConfigInit()
		* @brief: inits the engine configurations
		*/
		void ConfigInit();
		
		/*
		* @function : InstantiateModules()
		* @brief: Instantiate all the modules
		*/
		void InstantiateModules();

	public: 
		
		/*
		* @function : GetInstance()
		* @return: ref to static class Engine
		* @brief: Creates a singleton reference to Engine and returns it
		*/
		static Engine* GetInstance();
		void Run();

		/*setters*/
		inline void set_is_paused(bool is_paused) { is_paused_ = is_paused; };
		inline void set_is_running(bool is_engine_running) { is_engine_running_ = is_engine_running; }
		inline void set_is_scene_change(bool is_scene_restart) { is_scene_change_ =  is_scene_restart; };

		/*getters*/
		inline bool get_is_paused() { return is_paused_; }
		inline std::string Engine::get_version() { return "NoobEngine 0.1v";}
		inline int get_window_height() { return window_->get_height(); };

	private:

		int width_;
		int height_;
		
		bool is_paused_;
		bool is_engine_running_;
		bool is_scene_change_;

		std::string window_name_;

		gamewindow::Window* window_;

		static Engine* instance_;
	


#ifdef TEST_MODE

		component::GameObject* obj_;
#endif
	};
}


#endif