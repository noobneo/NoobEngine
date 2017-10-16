#include "enginelogger.h"
#include "../engine.h"
#include <Windows.h>
#include <iostream>

/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: enginelogger.cpp
Purpose: contains print methods for engine logger
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 14th October 2017
---------------------------------------------------------*/

namespace enginecore {

	void EngineDebugLogPrint(const char* msg_type, const char* format, ...) {

		const size_t max_chars = 220;
		char buffer[max_chars] = { 0 };

		sprintf_s(buffer, msg_type);
		strcat_s(buffer, format);
		strcat_s(buffer, "\n");

		const size_t total_size = max_chars + 1024;
		char log_msg[total_size] = { 0 };

		va_list arg_list;

		va_start(arg_list, format);
		vsnprintf_s(log_msg, total_size, buffer, arg_list);
		va_end(arg_list);

		std::cout << log_msg;
		//OutputDebugStringA(log_msg);
	}

#if defined(VERBOSITY_LEVEL)

	void EngineDebugLogPrint(const char* function_name , const int line_number, const char* format, ...) {

		const size_t max_chars = 220;
		char buffer[max_chars] = { 0 };

		sprintf_s(buffer, "Verbose : function name : %s line no : %d",function_name  , line_number);
		strcat_s(buffer, format);
		strcat_s(buffer, "\n");

		const size_t total_size = max_chars + 1024;
		char log_msg[total_size] = { 0 };

		va_list arg_list;

		va_start(arg_list, format);
		vsnprintf_s(log_msg, total_size, buffer, arg_list);
		va_end(arg_list);
	
		std::cout << log_msg;
		//OutputDebugStringA(log_msg);
	}

#endif
}