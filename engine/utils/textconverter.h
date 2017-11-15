#ifndef _TEXT_CONVERTER_H
#define _TEXT_CONVERTER_H

/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: textconverter.h
Purpose: Helps us get convert data types from string to float,bool,int,double or vice versa
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 17th October 2017
---------------------------------------------------------*/

#include <string>

namespace enginecore {

	namespace utils {

		class TextConverter
		{
		private:
			TextConverter() = default;
			~TextConverter()=default;

			TextConverter(const TextConverter&) = delete;
			TextConverter& operator=(const TextConverter&) = delete;


		public:
			static TextConverter*	GetInstance();

			void					Destroy();
#ifdef TEST_MODE
			void					TestTextConverter();
#endif

			int						GetIntFromString(std::string);
			bool					GetBoolFromString(std::string);
			float					GetFloatFromString(std::string);
			double					GetDoubleFromString(std::string);

			std::string				GetStringFromInt(int val);
			std::string				GetStringFromFloat(float val);
			std::string				GetStringFromDouble(double val);

			std::string				GetLowerCaseFromString(std::string text);
			std::string				GetUpperCaseFromString(std::string text);
		private:

			static TextConverter* instance_;

		};
	}
}

#endif // !_TEXT_CONVERTER_H
