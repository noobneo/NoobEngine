#ifndef _INPUT_HANDLER_H
#define _INPUT_HANDLER_H
#include "../../external/SDL2.0 Lib/include/SDL.h"

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

			const Uint8* current_key_board_state_;
			Uint8 previous_key_board_state_[MAX_KEYS];

			static InputHandler *instance_;

			SDL_Event event_;

		};
	}//inputhandler
}//enginecore

#endif // !_INPUT_HANDLER_H
