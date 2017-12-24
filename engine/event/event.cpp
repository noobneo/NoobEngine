
/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: event.cpp
Purpose: contains event related information
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 16th October 2017
---------------------------------------------------------*/



#include "event.h"

namespace enginecore {

	namespace events {

		int Event::event_id_ = 0;
		Event::Event() {

				type_ = E_EVENT_NONE;
				time_ =  0.0f;

				object_id_ =  -1;
	
				x_ = 0.0f ;
				y_ = 0.0f ;

				
				bullet_ = nullptr;

				body1_ = nullptr;
				body2_ = nullptr;
				missile_ = nullptr;
				player_ = nullptr;

				owner_id_ = -1;
				Event::event_id_++;
			
		}
		

	}
}
