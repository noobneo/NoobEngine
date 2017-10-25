/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Readme.md
Purpose: Features of Noob Engine
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 18th October 2017
---------------------------------------------------------*/

NoobEngine is ongoing projects which includes developing a game engine and game using that a part of CS529 course .

					*************************************************************************
					| 							Noob Engine v1.0v							|
					*************************************************************************
					
					
	
	Features 
	
	
	Engine.cpp
		-Singleton class which is responsible for starting enine instance
		- Initialising all the engine modules.
		- Running update loop
		- Shutting down the engine loop.
		- Shutting the modules
		
		
	FrameRateController
	*************************
	| /framecontroller.cpp  |
	| /timer.cpp   			|
	*************************

		- Calculate the fram rate between two frames
		- Caps the frams to MAX_FPS(for now 60.0f);
		
		
	Common
	*************************
	| /macros.h  			|
	*************************
	
		- Includes features which will be common to game and engine
		
	EngineLogger
	*************************
	| /enginelogger.cpp		|
	*************************
	
		- This provides feature to output logs
		- Debug level is based on if DEBUG is defined and on the VERBOSITY_LEVEL
		
		
	Inputhandler
	***********************************
	| /inputhandler.cpp 			  |
	| /keyboardeventdispatcher.cpp    |
	| /listener.cpp        			  |
	***********************************
	
		- Gets keyboard state from SDL_GetKeyboardState
		- Implemented Keyboard Dispacther and listener
		- Delegates and telecasts key states to listeners.
		- Class in which we want get keyboards need to register with keyboarddispatcher
		
		
	ResourceManager
	*************************
	| /resourcemanager.cpp  |
	| /textureloader.cpp    |
	| /sprite.cpp           |
	*************************
	
		- It is responsible for creating resources and giving it to user
		- Maintains a cache for the already loaded images
		- Returns a engine object Sprite* which can be used to manipulate the image.
		- it has textureloader which uses sdl to load bmps for now
		
	Renderer
		*************************
		| /renderer.cpp  		|
		*************************
		- Renderer is responsible for rendering the drawable objects which are added to its queue.
		- Uses SDL for now.
		
	Utils
		*****************************
		| /filehandler.cpp  		|
		| /textconverter.cpp   		|
		*****************************
		- It has FIlehandler and TExtconverter
		- it is used for reading files
		- we can use textconverter for converting string to int,float,double,bool and vice versa.
		
		
	Window 
	*************************
	| /wndow.cpp        	|
	*************************
		- it creates a window and window surface to draw on
		- it sets the window property.
		
		