
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

namespace enginecore {


	//static member initialization

	engine* engine::instance_ = nullptr;


	engine::engine() : width_(800), height_(800), is_paused_(false), window_name_("") {

		Init();
	}


	engine* engine::GetInstance() {

		if (!engine::instance_) {

			engine::instance_ = new engine();
		}
		return engine::instance_;
	}


	void engine::Init() {

		ENGINE_LOG("Engine Instance Created");
	}

	void engine::Update() {


	}

	void engine::ShutDown() {

		ENGINE_LOG("Shutting Down the engine");
		SAFE_DELETE(engine::instance_);
	}

	void engine::Pause() {


	}


	engine::~engine(){

		ENGINE_LOG("Engine Instance Destroyed");
	}

}
