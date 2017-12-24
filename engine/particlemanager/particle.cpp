

/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: particle.h
Purpose: particles
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 16th October 2017
---------------------------------------------------------*/



#include "GL\glew.h"
#include "particle.h"
#include "../graphics/shader.h"
#include "../graphics/renderer.h"
#include "../fpscontroller/fpscontroller.h"
#include "particlemanager.h"
namespace enginecore {

	namespace particlesystem {

		Particle::Particle() {

			r_ = 1.0f;
			g_ = 1.0f;
			b_ = 1.0f;
			a_ = 1.0f;
			next_ = nullptr;

			ml_matrix_ = maths::Mat4(1.0f);

			time_ = 0.5f;
			scale_ = .5f;
			id_ = -1;
			LoadMesh();
		}

		void Particle::SetColor(float r, float g, float b , float a) {

			r_ = r;
			g_ = g;
			b_ = b;
			a_ = a;
		}

		 Particle::~Particle() {

			glDeleteBuffers(1, &vbo_);
			//glDeleteBuffers(1, &cbo_);
		}

		void Particle::UpdateProperties(float x, float y, float scale, float r, float g, float b) {

			r_ = r;
			g_ = g;
			b_ = b;
			a_ = 1.0f;
			x_ = x;
			y_ = y;
			scale_ = scale;
			time_ = 0.5f;
		}

		void Particle::Reset() {

			r_ = 1.0f;
			g_ = 1.0f;
			b_ = 0.0f;
			a_ = 1.0f;
			time_ =0.5f;
			scale_ = .5f;
		}

		void Particle::Update() {

			a_ -= .05f;
			--y_;
			time_ -= fps::FpsController::GetInstance()->get_dt();
			ml_matrix_ = maths::Mat4::Translate(maths::Vec3(x_, y_, -3.0))* maths::Mat4::Rotate(0, maths::Vec3(0.0, 0.0, 1.0))* maths::Mat4::Scale(maths::Vec3(scale_, scale_, 0.0f));
		}

		void Particle::LoadMesh() {

			glGenBuffers(1, &vbo_);
			ConstructBuffers(vbo_);
		}

		void Particle::ConstructBuffers(unsigned int & vbo) {

			float w = 5.0f;
			float h = 5.0f;

			GLfloat  vertices[] = {
					// first triangle
					-w*0.5f,  -h*0.5f,0.0f,  // top right
					w*0.5f, -h*0.5f, 0.0f,  // bottom right
					w*0.5f,  h*0.5f, 0.0f,  // top left 
											// second triangle
					w*0.5f,  h*0.5f, 0.0f,  // bottom right
					-w*0.5f,  h*0.5f, 0.0f,  // bottom left
					-w*0.5f,  -h*0.5f, 0.0f   // top left
				};

				glBindBuffer(GL_ARRAY_BUFFER, vbo_);
				glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
		}


		void Particle::Render() {

			Update();
			graphics::Renderer::GetInstance()->ShapeSettings("modeling_matrix", ml_matrix_);
			glBindBuffer(GL_ARRAY_BUFFER, vbo_);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(0);

			graphics::Renderer::GetInstance()->get_shader()->SetUniform4f("color", maths::Vec4(r_ , g_ ,b_ ,a_));// ("modeling_matrix", ml_matrix_);

			glDrawArrays(GL_TRIANGLES, 0, 6);
			glBindBuffer(GL_ARRAY_BUFFER, 0);


		}

	}
}
