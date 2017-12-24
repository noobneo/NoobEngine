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

			void SetColor(float r, float g, float b , float a);

		
		private:

			Particle();
			~Particle();
			Particle(const Particle &) = delete;
			Particle  & operator=(const Particle &) = delete;

			void Reset();
			void Render();
			void Update();
			void LoadMesh();
			void UpdateProperties(float x, float y , float scale_, float r, float g, float b);
			void ConstructBuffers(unsigned int &vbo);

			inline void set_id(int id) { id_ = id; };
			inline int get_id() { return id_; };

			inline void set_next(Particle* next) { next_ = next; };
			inline Particle* get_next() {	return next_; };

			inline float get_time() { return time_; };
		
		public:

			

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
