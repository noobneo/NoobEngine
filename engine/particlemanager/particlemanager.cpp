

/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: particlemanager.cpp
Purpose: manages and creates particles
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 16th October 2017
---------------------------------------------------------*/



#include "particlemanager.h"
#include "../common/macros.h"
#include "particle.h"
#include "../enginelogger/enginelogger.h"
namespace enginecore{


	namespace particlesystem {

		ParticleManager* ParticleManager::instance_ = nullptr;

		ParticleManager::ParticleManager() {

			available_particle_ = nullptr;
			total_particles_ = 0;
			max_in_call_ = 8;
			min_in_call_ = 3;
			total_active_particles_ = 0;

			CreateParticlePool();
		}


		ParticleManager* ParticleManager::GetInstance() {

			if (!ParticleManager::instance_) {

				ParticleManager::instance_ = new ParticleManager();
			}

			return ParticleManager::instance_;
		}


		void ParticleManager::CreateParticlePool() {

			for (int i = 0; i < MAX_SIZE; ++i) {

				particle_pool_[i] = new Particle();
				particle_pool_[i]->set_id(i + ++total_particles_);
				particle_pool_[i]->set_next(available_particle_);
				available_particle_ = particle_pool_[i];
			}
		}

		void ParticleManager::GenerateParticle(float x, float y,float scale,int lowest , int highest, float r, float g, float b) {

			int particle_count = rand() % max_in_call_ + min_in_call_;	
			total_active_particles_ += particle_count;
			//int lowest = -50;
			//int highest = 50;
			int range = (highest - lowest) + 1;
			for (int i = 0; i < particle_count; ++i) {

				Particle* particle = GetParticle();
				if (particle) {

					active_particles_[particle->get_id()] = particle;
					float x1  = x+ lowest + int(range*rand() / (RAND_MAX + 1.0));
					float y1 =  y+ lowest + int(range*rand() / (RAND_MAX + 1.0));
					float time = (float)(rand() % 10);
					time *=.1f;

					particle->UpdateProperties(x1, y1,scale*time,r,g,b);
				}
			}
			ENGINE_ERR_LOG("total particles in use :%d",total_active_particles_);
		}

		Particle* ParticleManager::GetParticle() {

			if (!available_particle_) {

				ENGINE_ERR_LOG("No more particles in the poool");
				return nullptr;
			}

			Particle* temp = available_particle_;
			available_particle_ = available_particle_->get_next();
			return temp;
		}

		void ParticleManager::Reset() {

			for (auto &itr : active_particles_) {

				itr.second->set_next(available_particle_);
				available_particle_ = itr.second;
			}
			active_particles_.clear();

			remove_queue_.clear();
		}

		void ParticleManager :: RemoveInActiveParticles() {

			for (auto particle : remove_queue_) {

				particle->set_next(available_particle_);
				available_particle_ = particle;
				particle->Reset();
				active_particles_.erase(particle->get_id());
				--total_active_particles_;
			}
			remove_queue_.clear();
		}


		void ParticleManager::RenderParticles() {

			for (auto &it : active_particles_) {

				it.second->Render();
				if (it.second->get_time() <= 0) {

					remove_queue_.push_back(it.second);
				}
			}
		}


		void ParticleManager::Destroy() {

			for (int i = 0; i < 1; i++) {

				delete particle_pool_[i];
			}

			CLEAN_DELETE(ParticleManager::instance_);
	
		}
	}
}