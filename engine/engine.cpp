
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

#include <iostream>
#include "game-global.h" 
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
	EngineConfig* EngineConfig::EngineConfig::config_ = nullptr;

	Engine::Engine() : width_(1024), height_(800), is_paused_(false), is_engine_running_(false), window_name_(""), window_(nullptr){

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


	//	enginecore::serialize::Serializer::GetInstance()->LoadConfig("playground/resources/gamedata/engine-config.json" , );
		ConfigInit();

		width_ = EngineConfig::config_->screen_width_;
		height_ = EngineConfig::config_->screen_height_;

		window_ = new gamewindow::Window(width_, height_, EngineConfig::config_->game_name_);

		if (window_->CreateWindow()) {

			ENGINE_LOG("Initializing Engine Modules");
			InstantiateModules();
		//	Run();
		}
	}


	void Engine::ConfigInit() {

		EngineConfigData data = serialize::Serializer::GetInstance()->SerializeEngineData("playground/resources/engine-config.json");
		EngineConfig::config_ = new EngineConfig();
		EngineConfig::config_->fps_	 = data.fps_;
		EngineConfig::config_->debug_on_=  data.debug_on_		;
		EngineConfig::config_->texture_mode_=  data.texture_mode_	;
		EngineConfig::config_->ptm_ =  data.ptm_			;
		EngineConfig::config_->max_level_ =  data.max_level_		;
		EngineConfig::config_->max_recoil_ =  data.max_recoil_	;
		EngineConfig::config_->start_scene_ = data.start_scene_	;
		EngineConfig::config_->max_objects_  = data.max_objects_	;
		EngineConfig::config_->gravity_ =  data.gravity_		;
		EngineConfig::config_->screen_height_ = data.screen_height_;
		EngineConfig::config_->screen_width_ = data.screen_width_;
		EngineConfig::config_->game_name_ = data.game_name_;

	}


	void Engine::InstantiateModules() {

		//fps controller
		fps::FpsController::GetInstance();

		//file handler
		utils::FileHandler::GetInstance();

		//input handler
		inputhandler::InputHandler::GetInstance();


		//resourcemanager
		resourcemanager::ResourceManager::GetInstance();

		//renderer
		graphics::Renderer::GetInstance();
		graphics::Renderer::GetInstance()->StoreGameWindowData(window_->get_game_window(), window_->get_window_surface() , window_);
		graphics::Renderer::GetInstance()->Init();

		//gameobjectmanager
		component::GameobjectManager::GetInstance();

		//objectfactory 
		component::ComponentManager::GetInstance();


		//objectfactory 
		component::ObjectFactory::GetInstance();

		//serializer
		serialize::Serializer::GetInstance();

		//physicsmanager
		physics::PhysicsManager::GetInstance();

		//scenemanager
		common::SceneManager::GetInstance();

		//eventmanager
		events::EventManager::GetInstance();

		//particle sysetem
		particlesystem::ParticleManager::GetInstance();

		serialize::Serializer::GetInstance()->SerializeGameData(EngineConfig::config_->start_scene_);

	}


	void Engine::Run() {


		is_engine_running_ = true;

		std::string str;	
		char buf[100];
		//fps::FpsController::GetInstance()->GetStartFrameTick();

		//graphics::Renderer::GetInstance()->Init();
		while (true == is_engine_running_)
		{

			if ( inputhandler::InputHandler::GetInstance()->Update()) {

				if (is_scene_change_) {

					common::SceneManager::GetInstance()->ResetAndSerializeScene();
				}
					
				
				//else 
				{
					//start of loop
					fps::FpsController::GetInstance()->GetTimeSinceLastFrame();
					//fps::FpsController::GetInstance()->GetStartFrameTick();

					//PhysicsManager
					physics::PhysicsManager::GetInstance()->Update();

					//ComponentManager
					component::ComponentManager::GetInstance()->Update();

					//GameObjectManager
					component::GameobjectManager::GetInstance()->Update();

					//update
					graphics::Renderer::GetInstance()->Draw();

					//events
					events::EventManager::GetInstance()->Update(fps::FpsController::GetInstance()->get_dt());



					//end of loop
					fps::FpsController::GetInstance()->CapFrameRate();



					sprintf_s(buf, "%f", fps::FpsController::GetInstance()->get_dt());
					str = buf;
					window_->SetWindowName(str);
				}

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


		//resourcemanager
		resourcemanager::ResourceManager::GetInstance()->Destroy();

		//renderer
		graphics::Renderer::GetInstance()->Destroy();

		//gameobjectmanager
		component::GameobjectManager::GetInstance()->Destroy();

		//objectfactory 
		component::ComponentManager::GetInstance()->Destroy();

		//objectfactory 
		component::ObjectFactory::GetInstance()->Destroy();

		//serializer
		serialize::Serializer::GetInstance()->Destroy();

		//physicsmanager
		physics::PhysicsManager::GetInstance()->Destroy();


		//scenemanager
		common::SceneManager::GetInstance()->Destroy();

		//eventmanager
		events::EventManager::GetInstance()->Destroy();

		//particle sysetem
		particlesystem::ParticleManager::GetInstance()->Destroy();

		ENGINE_LOG("Engine Instance Destroyed");
		CLEAN_DELETE(window_);	

		CLEAN_DELETE(EngineConfig::config_);

		CLEAN_DELETE(Engine::instance_);


		ENGINE_LOG("Exiting Engine");
	}

	Engine::~Engine(){

		
	}

}
