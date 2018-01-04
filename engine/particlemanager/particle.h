#ifndef _BOUNDINGBOX_COMPONENT_H_
#define _BOUNDINGBOX_COMPONENT_H_

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



#include "../maths/vec2.h"
#include "../maths/mat4.h"

namespace enginecore {

	namespace particlesystem {

		class ParticleManager;
	
		class Particle 
		{

			/*
			* @function : SetColor(float r, float g, float b , float a)
			* param : r is the red value 
			* param : g is the green value
			* param : b is the blue value
			* param : a is the alpha value
			* @brief: Set the color for the particle
			*/
			void SetColor(float r, float g, float b , float a);
	
		private:

			//ctor
			Particle();
			Particle(const Particle &) = delete;
			Particle  & operator=(const Particle &) = delete;
			
			//dtor
			~Particle();

			/*
			* @function : Reset()
			* @brief: Resets the particle properties
			*/
			void Reset();

			/*
			* @function : Render()
			* @brief: Render particle the particle to the screen
			*/
			void Render();

			/*
			* @function : Update()
			* @brief: Updates the position and color 
			*/
			void Update();

			/*
			* @function : LoadMesh()
			* @brief: loads the vbo for particle
			*/
			void LoadMesh();


			/*
			* @function : UpdateProperties(float x, float y , float scale_, float r, float g, float b)
			* param : x is the x position value
			* param : y is the y position value
			* param : r is the red value
			* param : g is the green value
			* param : b is the blue value
			* @brief: updates the color and position properties of the particle
			*/
			void UpdateProperties(float x, float y , float scale_, float r, float g, float b);
			
			
			/*
			* @function : SetColor(float r, float g, float b , float a)
			* param : vbo is the vertext buffer for the particle
			* @brief: Creates the vbo
			*/
			void ConstructBuffers(unsigned int &vbo);


			//setters
			inline void set_id(int id) { id_ = id; };
			inline void set_next(Particle* next) { next_ = next; };


			//getters
			inline Particle* get_next() {	return next_; };
			inline int get_id() { return id_; };
			inline float get_time() { return time_; };

		private:

			friend class ParticleManager;
			
			Particle* next_;
			maths::Mat4 ml_matrix_;
		
			float time_;
			unsigned int vbo_;
			unsigned int cbo_;
			float r_;
			float g_;
			float b_;
			float a_;		
			float x_;
			float y_;
			float scale_;
			int id_;
		};

	}
}

#endif // _BODY_ANIMATION_COMPONENT_H_
