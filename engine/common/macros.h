#ifndef  _MACROS_H_
#define _MACROS_H_

/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: macros.h
Purpose: header files that includes the macros for the engine
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 16th October 2017
---------------------------------------------------------*/

#include <functional>   // std::bind

using namespace std::placeholders;

#define EPSILON 00000.1f

#define MAX_FPS 60.0f
#define FPS_SAMPLE_SIZE 60

#define CLEAN_DELETE(ptr)        do{ if(ptr) delete ptr; ptr=nullptr;}while(0);


#define CALLBACK(function_name,arg1,arg2) std::bind (function_name,arg1,arg2)   
#endif // ! __MACROS_H__
