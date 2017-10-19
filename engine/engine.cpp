
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
#include "fpscontroller\fpscontroller.h"
#include "utils\filehandler.h"

#include "inputhandler\inputhandler.h"
#include "inputhandler\keyboardlistener.h"

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
			InstantiateModules();

			is_engine_running_ = true;
			Run();
		}
	}



	void Engine::InstantiateModules() {

		//fps controller
		fps::FpsController::GetInstance();

		//file handler
		utils::FileHandler::GetInstance();

		//input handler
		inputhandler::InputHandler::GetInstance();

		
#ifdef TEST_MODE

		RegisterKeyBoardListener();
#endif


	}

	void Engine::Run() {


		std::string str;	
		char buf[100];
		fps::FpsController::GetInstance()->GetStartFrameTick();
		while (true == is_engine_running_)
		{

			if (inputhandler::InputHandler::GetInstance()->Update()) {

				fps::FpsController::GetInstance()->CheckFrameRate();
				fps::FpsController::GetInstance()->CapFrameRate();

				sprintf_s(buf, "%f", fps::FpsController::GetInstance()->get_dt());
				str = buf;
				window_->SetWindowName(str);
			}
			else {

				is_engine_running_ = false;
			}

		}//end of gamelooop


		ShutDown();
	}


	void Engine::Update() {


	}

	void Engine::ShutDown() {


		ENGINE_LOG("Shutting Down the engine");
		
		//fps module
		fps::FpsController::GetInstance()->Destroy();

		//utils
		utils::FileHandler::GetInstance()->Destroy();


		//inputmodule
		inputhandler::InputHandler::GetInstance()->Destroy();


		ENGINE_LOG("Engine Instance Destroyed");
		CLEAN_DELETE(window_);	

		CLEAN_DELETE(Engine::instance_);

		ENGINE_LOG("Exiting Engine");
	}

	void Engine::Pause() {


	}


#ifdef TEST_MODE

	void Engine::RegisterKeyBoardListener() {

		auto keyboard_listener= inputhandler::KeyboardListener::CreateListener();

		keyboard_listener->on_key_pressed_ = FUNCTION_CALLBACK(Engine::OnKeyPressed,this);
		keyboard_listener->on_key_released_ = FUNCTION_CALLBACK(Engine::OnKeyReleased, this);
	}


	void Engine::OnKeyPressed(const Uint8 * key_state) {

		if (key_state[SDL_SCANCODE_RIGHT]) {

			ENGINE_LOG("Right Pressed");

		}else if (key_state[SDL_SCANCODE_LEFT]) {

			ENGINE_LOG("Left Pressed");

		} else if (key_state[SDL_SCANCODE_UP]) {

			ENGINE_LOG("Up Pressed");

		}else if (key_state[SDL_SCANCODE_DOWN]) {

			ENGINE_LOG("Down Pressed");
		}
	}

	void Engine::OnKeyReleased(const Uint8 * key_state) {

		if (key_state[SDL_SCANCODE_RIGHT]) {

			ENGINE_LOG("Right Released");

		} else if (key_state[SDL_SCANCODE_LEFT]) {

			ENGINE_LOG("Left Released");

		} else if (key_state[SDL_SCANCODE_UP]) {

			ENGINE_LOG("Up Released");

		} else if (key_state[SDL_SCANCODE_DOWN]) {

			ENGINE_LOG("Down Released");
		}
	}
#endif


	Engine::~Engine(){

		
	}

}
