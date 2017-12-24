
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


#ifdef TEST_MODE
#include "../enginelogger/enginelogger.h"
#endif // TEST_MODE


namespace enginecore {

	namespace utils {

		FileHandler* FileHandler::instance_ = nullptr;


		FileHandler* FileHandler::GetInstance() {

			if (!FileHandler::instance_) {

				FileHandler::instance_ = new FileHandler();

				#ifdef TEST_MODE
					TextConverter::GetInstance()->TestTextConverter();
				#endif
			}

			

			return FileHandler::instance_;
		}


		std::string FileHandler::ReadFile(std::string filename) {

	
			FILE* file = fopen(filename.c_str() , "rt");
			fseek(file, 0, SEEK_END);

			unsigned long length = ftell(file);

#ifdef TEST_MODE
			ENGINE_LOG("File length : %d",length);
#endif


			char *buffer = new char[length + 1];
			memset(buffer, 0, length+1);
			fseek(file, 0, SEEK_SET);

			fread(buffer, sizeof(char), length, file);

			std::string filedata(buffer);

			delete[]buffer;
			fclose(file);

			return filedata;
		}
		
		void FileHandler::Destroy() {

			#ifdef TEST_MODE
				ENGINE_LOG("Destroying FileHandler");
			#endif

			TextConverter::GetInstance()->Destroy();
			CLEAN_DELETE(FileHandler::instance_);
		}
	}

}

