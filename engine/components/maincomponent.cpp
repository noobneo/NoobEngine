
/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: maincomponent.h
Purpose: base component class from which other components inherit
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 25th October 2017
---------------------------------------------------------*/

#include "mainComponent.h"

#ifdef TEST_MODE
#include "../enginelogger/enginelogger.h"
#endif // TEST_MODE

namespace enginecore {

	namespace component {

		MainComponent::MainComponent() {

			component_type_ = E_COMPONENT_TYPE_NONE;
			owner_ = nullptr;
		}


		MainComponent::~MainComponent() {
#ifdef TEST_MODE
			ENGINE_LOG("DEstroying the MainComponent ");
#endif // TEST_MODE
		}
	}
}