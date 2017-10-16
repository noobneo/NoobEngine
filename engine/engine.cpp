
/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: engine.cpp
Purpose: Start Point for engine
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 14th October 2017
---------------------------------------------------------*/

#include "engine-includes.h"

FILE _iob[] = { *stdin, *stdout, *stderr };

extern "C" FILE * __cdecl __iob_func(void)
{
	return _iob;
}

#pragma comment(lib, "legacy_stdio_definitions.lib")


namespace enginecore {

	//static member initialization

	Engine* Engine::instance_ = nullptr;


	Engine::Engine() : width_(800), height_(800), is_paused_(false), is_engine_running_(false), window_name_(""), window_(nullptr){

		Init();
	}


	Engine* Engine::GetInstance() {

		if (!Engine::instance_) {

			Engine::instance_ = new Engine();
		}
		return Engine::instance_;
	}


	void Engine::Init() {

		ENGINE_LOG("Engine Instance Created");

		window_ = new gamewindow::Window(width_, height_, "NoobEngine 0.1v");

		if (window_->CreateWindow()) {

			ENGINE_LOG("Initializing Engine Modules");
			is_engine_running_ = true;
			Run();
		}
	}


	void Engine::Run() {

		const float dt = 1.0f / 60.0f;


		Uint32 start_ticks, end_ticks;
		while (true == is_engine_running_)
		{
			SDL_Event e;
			while (SDL_PollEvent(&e) != 0)
			{
			
				start_ticks = SDL_GetTicks();

				//User requests quit
				if (e.type == SDL_QUIT)
				{
					is_engine_running_ = false;
				}

			
				end_ticks = SDL_GetTicks();

				/*while (end_ticks - start_ticks < end_ticks) {


				}*/

				ENGINE_LOG("my dt : %f , expected dt : %f ", end_ticks - start_ticks, dt);
			}
		}


		ShutDown();
	}


	void Engine::Update() {


	}

	void Engine::ShutDown() {

		ENGINE_LOG("Shutting Down the engine");
		
		CLEAN_DELETE(window_);	

		ENGINE_LOG("Engine Instance Destroyed");
		CLEAN_DELETE(Engine::instance_);

		ENGINE_LOG("Exiting Engine");
	}

	void Engine::Pause() {


	}


	/*getters*/

	std::string Engine::get_version() {

		return "NoobEngine 0.1v";
	}

	Engine::~Engine(){

		
	}

}
