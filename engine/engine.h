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

 namespace enginecore {

	class engine
	{
	private:
		engine();
		~engine();


		//disable copy constructor and copy assignment constructor
		engine(const engine& copy) = delete;
		engine& operator=(const engine& copy) = delete;

		void Init();

	public:
		
		void Update();
		void ShutDown();
		void Pause();

		static engine* GetInstance();


		inline bool get_is_paused() { return is_paused_; }

	private:

		int width_;
		int height_;
		
		bool is_paused_;

		std::string window_name_;

		static engine* instance_;
	};
}


#endif