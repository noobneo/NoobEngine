

#ifndef _SHADER_H_
#define _SHADER_H_

/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: shader.h
Purpose: file for reading and handling shader related properties 
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 16th October 2017
---------------------------------------------------------*/



#include "GL\glew.h"
#include "../maths/mat4.h"
#include "../maths/vec2.h"
#include "../maths/vec4.h"

#include <string>

namespace enginecore {

	namespace graphics {

		class Shader
		{
		public:
			Shader()=default;
			Shader(std::string vertex_shader_path, std::string fragment_shader_path);

			void enable() const;
			void disable() const;


			void SetUniform1f(const GLchar* name, const float&  val);
			void SetUniform1i(const GLchar* name, const int& val);

			void SetUniform2f(const GLchar* name, const maths::Vec2& vec4);
			void SetUniform3f(const GLchar* name, const maths::Vec3& vec3);
			void SetUniform4f(const GLchar* name, const maths::Vec4& vec2);


			void SetUniformMat4(const GLchar* name , const maths::Mat4& mat4);

			inline GLuint get_shader_id() { return shader_id_; };
			~Shader();

		private:

			GLuint Load();
			GLint GetUniformLocation(const GLchar* name);
		private:
			GLuint shader_id_;
			std::string vertex_shader_path_;
			std::string fragment_shader_path_;
		};

	}
}

#endif // !_SHADER_H_
