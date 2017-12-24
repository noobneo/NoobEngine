

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

#include "mouseeventdispatcher.h"
#include "../enginelogger/enginelogger.h"
#include "../common/macros.h"
#include "mouselistener.h"
#include "../engine.h"
#include "../graphics/renderer.h"

namespace enginecore {


	namespace inputhandler {

		MouseEventDispatcher*	MouseEventDispatcher::instance_ = nullptr;

		MouseEventDispatcher* MouseEventDispatcher::GetInstance() {

			if (!MouseEventDispatcher::instance_) {

				MouseEventDispatcher::instance_ = new MouseEventDispatcher();
			}

			return MouseEventDispatcher::instance_;
		}

		void MouseEventDispatcher::DispatchEvent(SDL_Event &event) {

			for (auto &it : listeners_) {

				try {
					if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP){

						//Get mouse position
						int x, y;
						SDL_GetMouseState(&x, &y);
						it.second->mouse_event_(event.type , (int)graphics::Renderer::GetInstance()->get_camera_pos().x_*-1+ x ,(int)graphics::Renderer::GetInstance()->get_camera_pos().y_+Engine::GetInstance()->get_window_height()-y);
					}
				}
				catch (const std::bad_function_call& e) {
					ENGINE_ERR_LOG("Bad Function Call :%s", e.what());
				}
			}
		}

		int MouseEventDispatcher::Register( MouseEventListener* listener) {

			if (!listener) {

				return -1;
			}

			++total_listeners_;
			listeners_[total_listeners_] = listener;
			return total_listeners_;
		}

		void MouseEventDispatcher::UnRegisterListeners() {

			for (auto &it : listeners_) {

				auto listener = it.second;
				--total_listeners_;
				CLEAN_DELETE(listener);
			}
			listeners_.clear();

		}

		void MouseEventDispatcher::Reset() {

			UnRegisterListeners();
		}

		void MouseEventDispatcher::Destroy() {

#ifdef TEST_MODE
			ENGINE_LOG("Destroying MouseEventDispatcher");
#endif // TEST_MODE

			UnRegisterListeners();
			CLEAN_DELETE(MouseEventDispatcher::instance_);
		}

	}
}
