

/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: sprite.cpp
Purpose: sprite for rendering
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 16th October 2017
---------------------------------------------------------*/




#include "GL\glew.h"
#include "sprite.h"

#ifdef TEST_MODE
#include "../enginelogger/enginelogger.h"
#endif // TEST_MODE
#include "renderer.h"
#include "../components/boundingbox.h"

#include "shader.h"
#include "../components/boundingbox.h"


namespace enginecore {

	namespace graphics {


		Sprite::Sprite() {


			rect_x_ = 1.0f;
			rect_w_ = 0.0;

			is_rect_animation_ = false;

			alpha_= 1.0f;
			z_order_ = 0;
			bounding_box_ = nullptr;
			position_.SetToZero(); 
			scale_.SetToZero();
			scale_.Set(1.0f,1.0f);
			rotate_ = 0.0f;

			anchorpoint_.Set(0.5f, 0.5f);

			width_ = 50;
			height_ = 50;
			data_ = nullptr;


			flip_x_ = 1.0f;
			flip_y_ = 1.0f;
		
			is_dirty_ = true;
			is_visible_ = true;
			active_ = false;
			is_texture_ = false;
			texture_mode_ = false;
	

			sprite_sheet_rows_ = 1;
			is_animated_sprite_ = false;
			total_frames_ = 1;
			current_frame_ = 0;
			animation_speed_counter_ = 0;
			animation_speed_ = 30;

			frame_x_ = 0.0f;
			frame_y_ = 0.0f;
			frame_width_ = 0.0f;
			frame_height_ = 0.0f;
			texture_width_ = 1.0;
			texture_height_ = 1.0;
			smoothness_ = 10.0f;
		}


		Sprite::Sprite(unsigned char* data, int width, int height , int channels):Sprite() {

			width_ = width;
			height_ = height;
			data_ = data;
			channels_ = channels;
			is_texture_ = true;
		}


		Sprite::~Sprite() {

			if (is_texture_) {

				glDeleteVertexArrays(1, &vao_);
				glDeleteTextures(1, &texture_);
			}

#ifdef DESTRUCTOR_LOG_MODE
			ENGINE_LOG("DEstroying the Sprite");
#endif // TEST_MODE

		}

		void Sprite::Init() {


			if (is_texture_) {

				GLfloat  vertices[32];

				frame_width_ = (float)width_ / total_frames_;
				frame_height_ = (float)height_ / sprite_sheet_rows_;

				texture_width_ = frame_width_ / width_;
				texture_height_ = frame_height_ / height_;

				if (anchorpoint_.get_x() == 0.0f && anchorpoint_.get_y() == 0.5f) {

					float temp[] = {
						// positions								// colors           // texture coords
						0.0f ,		   -frame_height_*0.5f, 0.0f,	1.0f, 0.0f, 0.0f,	frame_x_,				  frame_y_,
						frame_width_ , -frame_height_*0.5f, 0.0f,	0.0f, 1.0f, 0.0f,	texture_width_ + frame_x_,  frame_y_,
						frame_width_,  frame_height_*0.5f,  0.0f,	0.0f, 0.0f, 1.0f,	texture_width_ + frame_x_,  texture_height_ + frame_y_,
						0.0f,          frame_height_*0.5f,  0.0f,	1.0f, 1.0f, 0.0f,	frame_x_,				  texture_height_ + frame_y_
					};

					memcpy(vertices, temp, sizeof(temp));
				}

				else if (anchorpoint_.get_x() == 0.5f && anchorpoint_.get_y() == 1.0f) {

					float temp[] = {
						// positions								// colors           // texture coords
						-frame_width_*0.5f ,-frame_height_, 0.0f,	1.0f, 0.0f, 0.0f,		frame_x_,				  frame_y_,
						frame_width_ *0.5f, -frame_height_, 0.0f,	0.0f, 1.0f, 0.0f,		texture_width_ + frame_x_,  frame_y_,
						frame_width_ *0.5f,  0.0f,  0.0f,	0.0f, 0.0f, 1.0f,				texture_width_ + frame_x_,  texture_height_ + frame_y_,
						-frame_width_*0.5f,  0.0f,  0.0f,	1.0f, 1.0f, 0.0f,				frame_x_,				  texture_height_ + frame_y_
					};

					memcpy(vertices, temp, sizeof(temp));
				}
				else {

					float temp[] = {
						// positions									// colors				// texture coords
						-frame_width_*0.5f,  -frame_height_*0.5f, 0.0f,   1.0f, 0.0f, 0.0f,		frame_x_,  frame_y_,
						frame_width_*0.5f,   -frame_height_*0.5f, 0.0f,   0.0f, 1.0f, 0.0f,		texture_width_ + frame_x_, frame_y_,
						frame_width_*0.5f,    frame_height_*0.5f, 0.0f,   0.0f, 0.0f, 1.0f,		texture_width_ + frame_x_,  texture_height_ + frame_y_,
						-frame_width_*0.5f,   frame_height_*0.5f,	  0.0f,   1.0f, 1.0f, 0.0f,		frame_x_, texture_height_ + frame_y_
					};

					memcpy(vertices, temp, sizeof(temp));
				}




				if(is_animated_sprite_ && total_frames_ ==1 && sprite_sheet_rows_ ==1)
				{

					rect_w_ = frame_width_/ smoothness_;
					rect_w_ /= width_;
					frame_width_ = 1.0f;
					current_frame_ = 1;

					is_rect_animation_ = true;
				}



				unsigned int indices[] = {
					0, 1, 2, // first triangle
					2, 3, 0  // second triangle
				};

		
				glGenVertexArrays(1, &vao_);
				GLuint vbo , ebo;
				glGenBuffers(1, &vbo);
				glGenBuffers(1, &ebo);

				glBindVertexArray(vao_);

				glBindBuffer(GL_ARRAY_BUFFER, vbo);
				glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

				// position attribute
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
				glEnableVertexAttribArray(0);
				// color attribute
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
				glEnableVertexAttribArray(1);
				// texture coord attribute
				glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
				glEnableVertexAttribArray(2);
			
				// load and create a texture 
				// -------------------------

				glGenTextures(1, &texture_);
				glBindTexture(GL_TEXTURE_2D, texture_); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
													   // set the texture wrapping parameters
				glPixelStorei(GL_UNPACK_ALIGNMENT, channels_);
			
				// set texture filtering parameters
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				// load image, create texture and generate mipmaps
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

				if (channels_ == 4) {

					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, data_);
				}
				else {
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_, height_, 0, GL_RGB, GL_UNSIGNED_BYTE, data_);
				}
				glGenerateMipmap(GL_TEXTURE_2D);
				//stbi_image_free(data);
				glBindTexture(GL_TEXTURE_2D, 0);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
				glBindVertexArray(0);

				glDeleteBuffers(1, &vbo);
				glDeleteBuffers(1, &ebo);				

			}
		}


		void Sprite::UpdateProperties(component::MainComponent* boundingbox_) {

			bounding_box_ = static_cast<component::BoundingBoxComponent*>(boundingbox_);
		}

		void Sprite::CreateSpriteMap(std::vector<std::string> spriteframes) {

			int count = -1;
			for (auto it : spriteframes) {

				spriteframes_[it] = ++count;
			}
		}

		void Sprite::UpdateSpriteFrames() {
			

			if (!is_animated_sprite_) {

				return;
			}

			if (++animation_speed_counter_ >= animation_speed_) {

				animation_speed_counter_ = 0;

				if (is_rect_animation_) {

						rect_x_ += rect_w_;
				}
				else {

					current_frame_++;
					if (current_frame_ >= total_frames_) {

						current_frame_ = 0;
					}

				}
			}

		}

	
		void Sprite::SetSpriteFrame(std::string framename) {

			auto it = spriteframes_.find(framename);
			if (it != spriteframes_.end()) {

				current_frame_ = spriteframes_[framename];
			}
		}


		void Sprite::UpdatePosition() {

			if (!active_) {

				return;
			}

			is_dirty_ = true;
#ifdef USE_SDL
			bounding_box_.x = (int)position_x_;
			bounding_box_.y = (int)position_y_;
#else
			ml_matrix_ = maths::Mat4::Translate(maths::Vec3(position_.get_x(), position_.get_y(), -3.0))* maths::Mat4::Rotate(rotate_ , maths::Vec3(0.0,0.0,1.0))* maths::Mat4::Scale(maths::Vec3(scale_.get_x() , scale_.get_y(),0.0f));
#endif
		}


		void Sprite::SetScaleX(float scale_x) {

			scale_.set_x(scale_x);
	
		}

		void Sprite::SetScaleY(float scale_y) {

			scale_.set_y(scale_y);
		}

		void Sprite::SetScale(float scale_x, float scale_y) {

			scale_.set_x(scale_x);
			scale_.set_y(scale_y);
		}

		void Sprite::SetPosition(float position_x,float position_y) {

			position_.set_x(position_x);
			position_.set_y(position_y);
			UpdatePosition();
		}

		void Sprite::SetPositionX(float position_x) {

			position_.set_x(position_x);
			UpdatePosition();
		}

		void Sprite::SetPositionY(float position_y) {

			position_.set_y(position_y);
			UpdatePosition();
		}

		void Sprite::Draw() {
			
			if (!active_) {

				return;
			}

			if (bounding_box_) {
				bounding_box_->DrawShape();
			}
			UpdateSpriteFrames();
			DrawTexture();
		}

		void Sprite::DrawTexture() {

			if (!is_texture_ || !texture_mode_) {
				return;
			}

			Renderer::GetInstance()->TextureSettings("modeling_matrix", ml_matrix_);

			graphics::Renderer::GetInstance()->get_shader_texture()->SetUniform1i("frame_index", current_frame_);
			graphics::Renderer::GetInstance()->get_shader_texture()->SetUniform1f("texture_width_", texture_width_);
			graphics::Renderer::GetInstance()->get_shader_texture()->SetUniform1f("alpha", alpha_);
			graphics::Renderer::GetInstance()->get_shader_texture()->SetUniform1f("rect_x", rect_x_);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture_);
			glBindVertexArray(vao_);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,0);
			//glDrawArrays(GL_TRIANGLES, 0, 6);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindTexture(GL_TEXTURE_2D, 0);
			glBindVertexArray(0);
			Renderer::GetInstance()->ShapeMode();
		}

#ifdef TEST_MODE

		void Sprite::LeftRotation() {

			rotate_ += 1.0f;
		}

		void Sprite::RightRotation() {

			rotate_ -= 1.0f;
		}
#endif // TEST_MODE
		void Sprite::SetFlip(float flip_x, float flip_y) {

	
			if (flip_x_!=flip_x) {

				flip_x_ *= -1.0f;
				scale_.set_x(scale_.get_x()*-1.0f);

			}

			if (flip_y_ != flip_y) {

				flip_y_ *= -1.0f;
				scale_.set_y(scale_.get_y()*-1.0f);
			}

		}

		void  Sprite::SetFlipX(float flip_x) {

			SetFlip(flip_x, flip_y_);
		}

		void  Sprite::SetFlipY(float flip_y) {

			SetFlip(flip_x_, flip_y);
		}

		void Sprite::FlipX() {

			flip_x_ *= -1.0f;
			scale_.set_x(scale_.get_x()*-1.0f);

		}


		void Sprite::FlipY() {

			flip_y_ *= -1.0f;
			scale_.set_y(scale_.get_y()*-1.0f);
		}

		void Sprite::SetZorder(int z_order) {

			z_order_ = z_order;
			graphics::Renderer::GetInstance()->SortZ();

		}

	}
}
