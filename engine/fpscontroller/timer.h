#ifndef _TIMER_H_
#define _TIMER_H_


/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: timer.h
Purpose: header file for the time class responsible for ticks calculation 
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 16th October 2017
---------------------------------------------------------*/

namespace enginecore {

	namespace fps {

		class Timer
		{
		private:
			Timer();
			~Timer();
			
			Timer(const Timer&) = delete;
			Timer& operator=(const Timer&) = delete;

			void StartCounter();

		public:
			static Timer* GetInstance();
			
			
			void Init();
			void Destroy();
			void GetStartFrameTick();
	
			double GetStartCounter();
			double GetPerformceFrequency();

			/*float GetTicksLastFrame();*/
			float GetTicksSinceLastFrame();

		private:

			static Timer* instance_;

			double freq_;
			double start_counter_;
			double frame_start_ticks_;
			double frame_end_ticks_;
			float last_frame_time_;
		};
	}
}

#endif //!_TIMER_H_