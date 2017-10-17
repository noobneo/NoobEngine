#ifndef _FPS_CONTROLLER_H
#define _FPS_CONTROLLER_H


/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: fpscontroller.h
Purpose: contains methods for the fpscontroller class
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 16th October 2017
---------------------------------------------------------*/




#include "timer.h"
#include "../common/macros.h"


namespace enginecore {

	namespace fps {

		class FpsController
		{
		private:
			FpsController();
			~FpsController();

			FpsController(const FpsController&) = delete;
			FpsController& operator=(const FpsController&) = delete;

		public:



			void Step();
			void Destroy();
			
			void CapFrameRate();
			void CheckFrameRate();
			void GetStartFrameTick();
			/*void UpdateFrameRate();*/

			void SetFps(float fps);
			
			//getter

			inline float get_dt() { return dt_;}
			inline float get_current_fps() { return current_fps_; };
			inline float get_ideal_frame_rate() { return ideal_frame_rate_; };

			static FpsController* GetInstance();

		private:

			int counter_;

			float t_;
			float dt_;
			float current_fps_;
			float desired_fps_;
			float ideal_frame_rate_;
			
			Timer* timer_;

			static FpsController* instance_;


		};

	}

}

#endif // !_FPS_CONTROLLER_H
