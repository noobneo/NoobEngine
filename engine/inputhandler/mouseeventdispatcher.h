#ifndef MOUSE_EVENT_DISPATCHER_H_
#define MOUSE_EVENT_DISPATCHER_H_


/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: mouseeventdispatcher.h
Purpose: dispatches mouse events to the listeners
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 17th October 2017
---------------------------------------------------------*/




#include "../../external/SDL2.0 Lib/include/SDL_events.h"
#include <unordered_map>

namespace enginecore {

	namespace inputhandler {

		class MouseEventListener;

		class MouseEventDispatcher
		{
		public:

			static MouseEventDispatcher* GetInstance();


			void Destroy();
			void Reset();
			
			void DispatchEvent(SDL_Event& event_);
			int Register(MouseEventListener* listener);


			inline int get_total_listeners() { return total_listeners_; };

		private:
			MouseEventDispatcher() :total_listeners_(0) {}
			~MouseEventDispatcher() = default;

			void UnRegisterListeners();
			MouseEventDispatcher(const MouseEventDispatcher&) = delete;
			MouseEventDispatcher& operator=(const MouseEventDispatcher&) = delete;

		private:

			static MouseEventDispatcher* instance_;
			std::unordered_map<int, MouseEventListener*> listeners_;
			int total_listeners_;


		};


	}
}

#endif // MOUSE_EVENT_DISPTACHER_H_
