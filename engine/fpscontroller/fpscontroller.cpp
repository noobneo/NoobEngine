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

namespace enginecore {

	namespace fps {

		FpsController* FpsController::instance_ = nullptr;

		FpsController::FpsController() {

			desired_fps_ = MAX_FPS;
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

		void FpsController::CheckFrameRate() {

			dt_ = timer_->GetTicksSinceLastFrame();	
		}

		/*void FpsController::UpdateFrameRate() {

			dt_ = timer_->GetTicksLastFrame();
		}*/

		void FpsController::Step() {

			t_ += dt_;

			//ENGINE_LOG("dt:%f",1.0f/(dt_*10));
		}

		void FpsController::CapFrameRate() {

	/*		while (dt_ < ideal_frame_rate_) {

				dt_ = timer_->GetTicksLastFrame(); 	
			}*/

			float diff = ideal_frame_rate_ - dt_;
			Sleep(DWORD(diff));		
			Step();
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
