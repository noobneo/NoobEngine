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

#include "timer.h"

#include <Windows.h>
#include <iostream>


#include "../enginelogger/enginelogger.h"
#include "../common/macros.h"


namespace enginecore {

	namespace fps {

		Timer* Timer::instance_ = nullptr;

		Timer::Timer()	{

			freq_ = 0.0f;
			start_counter_ = 0.0f;
			last_frame_time_ = 0.0f;
			frame_end_ticks_ = 0.0f;
			frame_start_ticks_ = 0.0f;

			Init();

		}

		Timer::~Timer()	{

		}

		Timer* Timer::GetInstance() {

			if (!Timer::instance_) {

				Timer::instance_ = new Timer();
			}

			return Timer::instance_;
		}


		void Timer::Init() {

			///ENGINE_ASSERT(freq_-freq_<EPSILON);

			StartCounter();
		}

		void Timer::StartCounter() {

			LARGE_INTEGER li;
			if (!QueryPerformanceFrequency(&li)) {

				ENGINE_ERR_LOG("QueryPerformanceFrequency failed!");
			}

			freq_ = double(li.QuadPart) / 1000.0f;

			QueryPerformanceCounter(&li);
			start_counter_ = double(li.QuadPart);
		}



		void Timer::GetStartFrameTick() {

			LARGE_INTEGER li;
			QueryPerformanceCounter(&li);

			frame_start_ticks_ = double(li.QuadPart);
		}


		float Timer::GetTicksSinceLastFrame() {

			LARGE_INTEGER li;
			QueryPerformanceCounter(&li);

			frame_end_ticks_ = double(li.QuadPart);
			

			float dt = float((frame_end_ticks_ - frame_start_ticks_) / GetPerformceFrequency());
			frame_start_ticks_ = frame_end_ticks_;

			//	ENGINE_LOG("%f", dt);

			return dt;
		}




		/*float Timer::GetTicksLastFrame() {

			LARGE_INTEGER li;
			QueryPerformanceCounter(&li);

			frame_end_ticks_ = double(li.QuadPart);


			float dt = float((frame_end_ticks_ - frame_start_ticks_) / GetPerformceFrequency());
		
			//	ENGINE_LOG("%f", dt);

			return dt;
		}
		*/


		double Timer::GetPerformceFrequency() {

			LARGE_INTEGER li;
			QueryPerformanceCounter(&li);

			freq_ = double(li.QuadPart) / 1000.0f;

			return freq_;
		}

		double Timer::GetStartCounter() {

			LARGE_INTEGER li;
			QueryPerformanceCounter(&li);
			return double(double(li.QuadPart) - double(start_counter_)) / freq_;
		}

		void Timer::Destroy() {

			#ifdef TEST_MODE
				ENGINE_LOG("Destroying Timer");
			#endif // TEST_MODE

			CLEAN_DELETE(Timer::instance_);
		}

	}
}
