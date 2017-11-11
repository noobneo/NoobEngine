#ifndef _ENGINE_LOGGER_H_
#define _ENGINE_LOGGER_H_

/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: enginelogger.h
Purpose: logging for engine
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 14th October 2017
---------------------------------------------------------*/

	//*****************************************************//
    //	A simple logger class which outputs engine logs	  //	
	//	based on the debug level and verbosity      	  //
    //***************************************************//


	/*
	Define DEBUG in debug mode 

	VERBOSITY_LEVEL 
	In debug mode set VERBOSITY_LEVEL to 0 or 1

		Mode: Debug
		VERBOSITY_LEVEL  =1
			- enables all debug logs, error logs and verbose.
		VERBOSITY_LEVEL = 0
		    - enables debug log and error logs.


		Mode : Release
		VERBOSITY_LEVEL = 1
			- enables log and errors
		VERBOSITY_LEVEL = 0
			- disable all logs
	*/

#if defined(DEBUG)

	#if defined(VERBOSITY_LEVEL)
	
		#define ENGINE_LOG(format,...)				enginecore::EngineDebugLogPrint("Engine Debug Log : " , (format) , __VA_ARGS__)
		#define ENGINE_ERR_LOG(format,...)			enginecore::EngineDebugLogPrint("Engine Error Log : " , (format) , __VA_ARGS__)
		#define ENGINE_VERBOSE_LOG(format,...)		enginecore::EngineDebugLogPrint("Engine Verbose Log : " , (format) , __VA_ARGS__)
		
	#else

		#define ENGINE_LOG(format,...)				enginecore::EngineDebugLogPrint("Engine Debug Log : " , (format) , __VA_ARGS__)
		#define ENGINE_ERR_LOG(format,...)			enginecore::EngineDebugLogPrint("Engine Error Log : " , (format) , __VA_ARGS__)
		#define ENGINE_VERBOSE_LOG(format,...)		

	#endif

#else

	#if defined(VERBOSITY_LEVEL)

		#define ENGINE_LOG(format,...)				enginecore::EngineDebugLogPrint("Engine Debug Log : " , (format) , __VA_ARGS__)
		#define ENGINE_ERR_LOG(format,...)			enginecore::EngineDebugLogPrint("Engine Error Log : " , (format) , __VA_ARGS__)
		#define ENGINE_VERBOSE_LOG(format,...)		

	#else

		#define ENGINE_LOG(format,...)				
		#define ENGINE_ERR_LOG(format,...)			
		#define ENGINE_VERBOSE_LOG(format,...)		

	#endif

#endif // DEBUG


namespace enginecore {
	void EngineDebugLogPrint(const char* msg_type, const char* format, ...);
#if defined(VERBOSITY_LEVEL)
	void EngineDebugLogPrint(const char* function_name, const int line_number, const char* format, ...);
#endif
}

#endif // !

