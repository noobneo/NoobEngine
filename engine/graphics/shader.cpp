
/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: shader.cpp
Purpose: file for reading and handling shader related properties
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 16th October 2017
---------------------------------------------------------*/




#include "shader.h"

#include "../utils/filehandler.h"
#include "../enginelogger/enginelogger.h"

namespace enginecore {

	namespace graphics {


		Shader::Shader(std::string vertex_shader_path, std::string fragment_shader_path)
			: vertex_shader_path_(vertex_shader_path) , fragment_shader_path_(fragment_shader_path){

			shader_id_ = Load();
		}

		Shader::~Shader() {

			glDeleteProgram(shader_id_);
		}

		GLuint Shader::Load() {

			GLuint program = glCreateProgram();
			GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
			GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

			std::string vertex_string = utils::FileHandler::GetInstance()->ReadFile(vertex_shader_path_);
			std::string fragment_string = utils::FileHandler::GetInstance()->ReadFile(fragment_shader_path_);
			
			const char* fragment_source = fragment_string.c_str();
			const char* vertex_source = vertex_string.c_str();

			glShaderSource(vertex, 1, &vertex_source, NULL);
			glCompileShader(vertex);

			GLint result;

			glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);

			if (result == GL_FALSE) {

				char buffer[1024];
				glGetShaderInfoLog(vertex, 1024, 0, buffer);
				ENGINE_ERR_LOG("Shader compilation failed : %s ", buffer);
				glDeleteShader(vertex);
			}


			glShaderSource(fragment, 1, &fragment_source, NULL);
			glCompileShader(fragment);


			glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);

			if (result == GL_FALSE) {

				char buffer[1024];
				glGetShaderInfoLog(fragment, 1024, 0, buffer);
				ENGINE_ERR_LOG("Shader compilation failed : %s ",buffer);
				glDeleteShader(fragment);
			}

			glAttachShader(program , vertex);
			glAttachShader(program , fragment);


			glLinkProgram(program);
			glValidateProgram(program);


			glDeleteShader(vertex);
			glDeleteShader(fragment);

			return program;
		}


		void Shader::enable() const {

			glUseProgram(shader_id_);
		}

		void Shader::disable() const{

			glUseProgram(0);
		}

		void Shader::SetUniform1f(const GLchar* name, const float&  val) {

			glUniform1f(GetUniformLocation(name), val);
		}

		void Shader::SetUniform1i(const GLchar* name, const int& val) {

			glUniform1i(GetUniformLocation(name), val);
		}

		void Shader::SetUniform2f(const GLchar* name, const maths::Vec2& vec2) {

			glUniform2f(GetUniformLocation(name), vec2.get_x() , vec2.get_y());
		}

		void Shader::SetUniform3f(const GLchar* name, const maths::Vec3& vec3) {

			glUniform3f(GetUniformLocation(name), vec3.get_x(), vec3.get_y(), vec3.get_z());
		}

		void Shader::SetUniform4f(const GLchar* name, const maths::Vec4& vec4) {

			glUniform4f(GetUniformLocation(name), vec4.get_x(), vec4.get_y(), vec4.get_z(), vec4.get_w());
		}


		void Shader::SetUniformMat4(const GLchar* name, const maths::Mat4& mat4) {

			glUniformMatrix4fv(GetUniformLocation(name),1,GL_TRUE,mat4.elements);
		}

		GLint Shader::GetUniformLocation(const GLchar* name) {

			return glGetUniformLocation(shader_id_, name);
		}

	}

}