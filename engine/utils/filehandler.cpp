
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

#include "filehandler.h"
#include "../common/macros.h"
#include "textconverter.h"

namespace enginecore {

	namespace utils {

		FileHandler* FileHandler::instance_ = nullptr;


		FileHandler* FileHandler::GetInstance() {

			if (!FileHandler::instance_) {

				FileHandler::instance_ = new FileHandler();
			}

			TextConverter::GetInstance()->TestTextConverter();

			return FileHandler::instance_;
		}

		
		void FileHandler::Destroy() {

			TextConverter::GetInstance()->Destroy();
			CLEAN_DELETE(FileHandler::instance_);
		}
	}

}

