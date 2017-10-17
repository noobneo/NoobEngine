#ifndef _ASSERT_H_
#define _ASSERT_H_

/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: assert.h
Purpose: Implementation for Assert
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 16th October 2017
---------------------------------------------------------*/

#include <assert.h>

namespace enginecore {

	namespace Assert {

#define ENGINE_ASSERT(cond)						assert(cond)

	}
}

#endif // !_ASSERT_H_