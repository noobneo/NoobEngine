#ifndef _FILE_HANDLER_
#define _FILE_HANDLER_

/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: filehandler.cpp
Purpose: Helps us read a file 
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 17th October 2017
---------------------------------------------------------*/

#include<string>

namespace enginecore {

	namespace utils {


	class FileHandler
	{


	public :

		/*
		* @function : ReadFile(std::string filename)
		* @return: string of the file read
		* @brief: Reads the file and returns the content as string
		*/
		std::string ReadFile(std::string filename);


		/*
		* @function : Destroy()
		* @brief: destory the reference to the FileHandler
		*/
		void Destroy();

		/*
		* @function : GetInstance()
		* @return: static reference to the class FileHandler
		* @brief: creates and returns the singleton reference to the FileHandler
		*/
		static FileHandler* GetInstance();

	private:
		//ctor
		FileHandler() = default;

		//dtor
		~FileHandler() = default;
	
		FileHandler(const FileHandler&) = delete;
		FileHandler& operator=(const FileHandler&) = delete;


		
		
	private:

		static FileHandler* instance_;

	};

	}
}

#endif // !_FILE_HANDLER_
