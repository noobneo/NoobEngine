/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: inputhandler.h
Purpose: manages keyboard input and delegates the events to keyboardeventdispatcher
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 17th October 2017
---------------------------------------------------------*/


#ifndef _INPUT_HANDLER_H
#define _INPUT_HANDLER_H
#include "../../external/SDL2.0 Lib/include/SDL_scancode.h"
#include "../../external/SDL2.0 Lib/include/SDL_events.h" 

#define KEY_CODE SDL_Scancode 
#define MAX_KEYS 512

namespace enginecore {

	namespace inputhandler {

		class InputHandler
		{

		public:
			static InputHandler* GetInstance();


			bool Update();
			void Destroy();

			bool IsKeyPressed(KEY_CODE key);
			bool IsKeyReleased(KEY_CODE key);

			bool IsKeyTriggered(KEY_CODE key);

		private:
			InputHandler();
			~InputHandler();

			void DelegateKeyReleased();
			void DelegateKeyPressed();

		private:

			const Uint8* pump_state_;
			const Uint8* current_key_board_state_;
			Uint8 previous_key_board_state_[MAX_KEYS];

			static InputHandler *instance_;

			SDL_Event event_;

		};
	}//inputhandler
}//enginecore

#endif // !_INPUT_HANDLER_H
