
/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: boundingbox.cpp
Purpose: bounding box for debug mode
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 16th October 2017


---------------------------------------------------------*/


#include "GL\glew.h"
#include "boundingbox.h"
#include <string>
#include "../graphics/renderer.h"
#include "transformcomponent.h"
#include "gameobject.h"
#include "../graphics/shader.h"
#include "../game-global.h"
namespace enginecore {

	namespace component {

		BoundingBoxComponent::BoundingBoxComponent() {


			bound_width_ = 50;
			bound_height_ = 50;
			anchorpoint_.Set(0.5f, 0.5f);
			r_ = 1.0f;
			g_ = 0.0f;
			b_ = 0.0f;
		}


		void BoundingBoxComponent::Update() {

			if (!active_ || !enginecore::EngineConfig::config_->debug_on_) {

				return;
			}

			ml_matrix_ = maths::Mat4::Translate(maths::Vec3(transform_->get_position_x(), transform_->get_position_y(), -3.0))* maths::Mat4::Rotate(transform_->get_rotation(), maths::Vec3(0.0, 0.0, 1.0))* maths::Mat4::Scale(maths::Vec3(transform_->get_scale_x(), transform_->get_scale_x(), 0.0f));


		//	DrawShape();
		}

		void BoundingBoxComponent::Init(GameObject* owner) {

			owner_ = owner;
		}


		BoundingBoxComponent::~BoundingBoxComponent() {
			Reset();
		}

		void BoundingBoxComponent::SetColor(float r, float g, float b , float a) {

			r_ = r;
			g_ = g;
			b_ = b;
			a_ = a;
		}

		void BoundingBoxComponent::Reset() {

			bound_width_ = 50;
			bound_height_ = 50;
			glDeleteBuffers(1, &vbo_);
		}

		void BoundingBoxComponent::HandleEvent(events::Event *event) {

		}

		void BoundingBoxComponent::UpdateProperties() {

			transform_ = static_cast<TransformComponent*>(owner_->GetComponent(E_COMPONENT_TYPE_TRANSFORM));
			LoadMesh();
		}


		void BoundingBoxComponent::LoadMesh() {

			glGenBuffers(1, &vbo_);
			ConstructBuffers(vbo_);

		}

		void BoundingBoxComponent::ConstructBuffers(unsigned int & vbo) {

			GLfloat  vertices[18];

			float w = (float)bound_width_;
			float h = (float)bound_height_;

			if (anchorpoint_.get_x() == 0.5f && anchorpoint_.get_y() == 1.0f) {

				GLfloat  temp[] = {
					// first triangle
					-w*0.5f,  -h*1.0f,0.0f,  // top right
					w*0.5f, -h*1.0f, 0.0f,  // bottom right
					w*0.5f,  h*0.0f, 0.0f,  // top left 
									   // second triangle
									   w*0.5f,  h*0.0f, 0.0f,  // bottom right
									   -w*0.5f,  h*0.0f, 0.0f,  // bottom left
									   -w*0.5f,  -h*1.0f, 0.0f   // top left
				};
				memcpy(vertices, temp, sizeof(temp));
			}
			
			else if (anchorpoint_.get_x() == 0.0f && anchorpoint_.get_y() == 0.5f) {

				GLfloat  temp[] = {
					// first triangle
					-w*0.0f,  -h*0.5f,0.0f,  // top right
					w, -h*0.5f, 0.0f,  // bottom right
					w,  h*0.5f, 0.0f,  // top left 
									   // second triangle
									   w,  h*0.5f, 0.0f,  // bottom right
									   -w*0.0f,  h*0.5f, 0.0f,  // bottom left
									   -w*0.0f,  -h*0.5f, 0.0f   // top left
				};
				memcpy(vertices, temp, sizeof(temp));
			}
			else {

				

				GLfloat  temp[] = {
					// first triangle
					-w*0.5f,  -h*0.5f,0.0f,  // top right
					w*0.5f, -h*0.5f, 0.0f,  // bottom right
					w*0.5f,  h*0.5f, 0.0f,  // top left 
											// second triangle
											w*0.5f,  h*0.5f, 0.0f,  // bottom right
											-w*0.5f,  h*0.5f, 0.0f,  // bottom left
											-w*0.5f,  -h*0.5f, 0.0f   // top left
				};
				memcpy(vertices, temp, sizeof(temp));
	
			}


			glBindBuffer(GL_ARRAY_BUFFER, vbo_);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}


		void BoundingBoxComponent::DrawShape() {

			if (!active_ || !enginecore::EngineConfig::config_->debug_on_) {

				return;
			}

			graphics::Renderer::GetInstance()->ShapeSettings("modeling_matrix", ml_matrix_);
			glBindBuffer(GL_ARRAY_BUFFER, vbo_);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(0);

			graphics::Renderer::GetInstance()->get_shader()->SetUniform4f("color", maths::Vec4(r_ , g_ ,b_ ,a_));// ("modeling_matrix", ml_matrix_);


			glDrawArrays(GL_LINE_LOOP, 0, 6);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

		
		}

	}
}
