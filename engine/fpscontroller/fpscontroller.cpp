/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: fpscontroller.cpp
Purpose: calculates the dt and caps the frame rate
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 16th October 2017
---------------------------------------------------------*/

#include "fpscontroller.h"


#include "../assert/assert.h"
#include "../enginelogger/enginelogger.h"
#include <Windows.h>
#include "../game-global.h"

namespace enginecore {

	namespace fps {

		FpsController* FpsController::instance_ = nullptr;

		FpsController::FpsController() {

			desired_fps_ = enginecore::EngineConfig::config_->fps_;
			current_fps_ = 0.0f;
			ideal_frame_rate_ = 1000.0f / desired_fps_; // its in milliseconds

			timer_ = Timer::GetInstance();

		}


		void FpsController::SetFps(float fps) {

			if(fps > MAX_FPS) {

				fps = MAX_FPS;
				ENGINE_VERBOSE_LOG("Fps Could not be set to more than %d", __FUNCTION__,MAX_FPS);
			}

			desired_fps_ = fps < 0 ? MAX_FPS : fps;
			ideal_frame_rate_ = 1000.0f / desired_fps_;
		}

		FpsController* FpsController::GetInstance() {

			if (!FpsController::instance_) {

				FpsController::instance_ = new FpsController();
			}
			return FpsController::instance_;
		}


		void FpsController::GetStartFrameTick() {

			timer_->GetStartFrameTick();
		}

		void FpsController::GetTimeSinceLastFrame() {

#ifdef SDL_TICKS
			 timer_->GetStartTicks();
#else
			dt_ = timer_->GetTimeSinceLastFrame();	

#endif // SDL_TICKS
		//	dt_ *= 100.0f;
		}

		/*void FpsController::UpdateFrameRate() {

			dt_ = timer_->GetTicksLastFrame();
		}*/

		void FpsController::Step() {

			t_ += dt_;

			//ENGINE_LOG("dt:%f",1.0f/(dt_*10));
		}
	/*	1 / 60;
		0.0167-- > seconds;
		0.0167 * 1000 - >milli seconds

			16.67*/

void FpsController::CapFrameRate() {

#ifdef SDL_TICKS
	float diff = timer_->GetEndTicks();

	while (diff < ideal_frame_rate_) {

		diff = timer_->GetEndTicks();
	}

	dt_ = diff *.001f;

	/*assum paused or break point*/
	if (dt_ > .1f) {

		dt_ = 0.167f;
	}

#else
		float diff = ideal_frame_rate_ - dt_;
		diff = diff > 0.0f ? diff : 0.0f;
		Sleep(DWORD(diff));

		//CheckFrameRate();
		Step();

#endif // SDL_TICKS


		}

		void FpsController::Destroy() {

			#ifdef TEST_MODE
				ENGINE_LOG("Destroying Fps Controller");
			#endif // TEST_MODE

			Timer::GetInstance()->Destroy();

			CLEAN_DELETE(FpsController::instance_);
		}


		FpsController::~FpsController(){

		}

	}

}
