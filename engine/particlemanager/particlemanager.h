

#ifndef PARTICLE_MANAGER_H_
#define PARTICLE_MANAGER_H_

/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: particlemanager.h
Purpose: manages and creates particles
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 16th October 2017
---------------------------------------------------------*/



#include "../game-global.h"
#include <unordered_map>

namespace enginecore {

	namespace graphics {

		class Renderer;
	}
}

namespace enginecore {

	namespace particlesystem {

		class Particle;
		class ParticleManager
		{

		public:

			static ParticleManager* GetInstance();
			void GenerateParticle(float x, float y, float scale, int lowest, int highest,float r, float g, float b);

			void Reset();

			void Destroy();

		private:
			ParticleManager();
			~ParticleManager()=default;
			ParticleManager(const ParticleManager&) = delete;
			ParticleManager& operator=(const ParticleManager&) = delete;


			void CreateParticlePool();
			void RemoveInActiveParticles();
			void RenderParticles();
			Particle* GetParticle();
		private:

			friend class graphics::Renderer;

			int total_particles_;
			static ParticleManager* instance_;
			Particle* particle_pool_[MAX_SIZE];
			Particle* available_particle_;
			std::unordered_map<int, Particle*> active_particles_;
			std::vector<Particle*> remove_queue_;
			int max_in_call_;
			int min_in_call_;
			int total_active_particles_;

		};
	}
}

#endif // !PARTICLE_MANAGER_H_
