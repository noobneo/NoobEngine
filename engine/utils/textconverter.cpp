/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: textconverter.cpp
Purpose: Helps us get convert data types from string to float,bool,int,double or vice versa
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 17th October 2017
---------------------------------------------------------*/

#include "textconverter.h"
#include "../common/macros.h"
#include <locale>         // std::locale, std::tolower

#ifdef TEST_MODE
#include "../enginelogger/enginelogger.h"
#include "filehandler.h"
#endif // TEST_MODE

namespace enginecore {

	namespace utils {

		TextConverter* TextConverter::instance_ = nullptr;


		TextConverter* TextConverter::GetInstance() {

			if (!TextConverter::instance_) {

				TextConverter::instance_ = new TextConverter();
			}

			return TextConverter::instance_;
		}

		int TextConverter::GetIntFromString(std::string val) {

			std::string::size_type sz;   // alias of size_t

			return std::stoi(val, &sz);
		}

		bool TextConverter::GetBoolFromString(std::string val) {

			if (strcmp("false", val.c_str()) == 0 || strcmp("FALSE", val.c_str()) == 0 || strcmp("False", val.c_str()) == 0 || strcmp("0", val.c_str()) == 0)
				return false;
			else
				return true;
		}

		float TextConverter::GetFloatFromString(std::string val) {

			std::string::size_type sz;   // alias of size_t

			return std::stof(val, &sz);
		}

		double TextConverter::GetDoubleFromString(std::string val) {

			std::string::size_type sz;   // alias of size_t

			return std::stod(val, &sz);
		}

		std::string TextConverter::GetStringFromInt(int val) {

			char buff[100];

			sprintf_s(buff, "%d", val);
			std::string str(buff);
			return str;
		}

		std::string TextConverter::GetStringFromFloat(float val) {

			char buff[100];

			sprintf_s(buff, "%f", val);
			std::string str(buff);
			return str;
		}

		std::string TextConverter::GetStringFromDouble(double val) {

			char buff[100];

			sprintf_s(buff, "%f", val);
			std::string str(buff);
			return str;
		}


		std::string	TextConverter::GetLowerCaseFromString(std::string text) {

			std::locale loc;
			std::string lower_case;
			for (std::string::size_type i = 0; i < text.length(); ++i) {

				lower_case += std::tolower(text[i], loc);
			}

			return lower_case;
		}


		std::string	TextConverter::GetUpperCaseFromString(std::string text) {


			std::locale loc;
			std::string lower_case;
			for (std::string::size_type i = 0; i < text.length(); ++i) {

				lower_case += std::toupper(text[i], loc);
			}

			return lower_case;
		}



		void TextConverter::Destroy() {

			#ifdef TEST_MODE
				ENGINE_LOG("Destroying TextConverter");
			#endif
			CLEAN_DELETE(TextConverter::instance_);
		}




		/*Tests  TextConverter*/
#ifdef TEST_MODE
		void TextConverter::TestTextConverter() {


			int val_i = 129328;
			float val_f = 12321.45345f;
			double val_d = 12321.45345f;


			ENGINE_LOG("Printing String from int(129328) : %s", GetStringFromInt(val_i).c_str());
			ENGINE_LOG("Printing String from float(12321.45345f): %s", GetStringFromFloat(val_f).c_str());
			ENGINE_LOG("Printing String from double(12321.45345f): %s", GetStringFromDouble(val_d).c_str());


			std::string str_i("1231212");
			std::string str_f("1231212.09123");
			std::string str_d("1231212.1923812");
			std::string str_b1("1");
			std::string str_b2("0");
			std::string str_b3("false");
			std::string str_b4("true");


			ENGINE_LOG("Printing Int from string (1231212) : %d", GetIntFromString(str_i));
			ENGINE_LOG("Printing double from string (1231212.1923812) : %f", GetDoubleFromString(str_d));
			ENGINE_LOG("Printing float from string (1231212.09123) : %f", GetFloatFromString(str_f));
			ENGINE_LOG("Printing bool from string (1) : %i", GetBoolFromString(str_b1));
			ENGINE_LOG("Printing bool from string (0) : %i", GetBoolFromString(str_b2));
			ENGINE_LOG("Printing bool from string (false) : %i", GetBoolFromString(str_b3));
			ENGINE_LOG("Printing bool from string (true) : %i", GetBoolFromString(str_b4));

			//ENGINE_LOG("File Text : %s", FileHandler::GetInstance()->ReadFile("README.md").c_str());


		}
#endif

	}
}
