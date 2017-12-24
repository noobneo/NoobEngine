
/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: bossai.cpp
Purpose: boss ai component behaviour
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 16th October 2017


---------------------------------------------------------*/
#include "bossai.h"
#include "bodycomponent.h"
#include "gameobject.h"

namespace enginecore {

	namespace component {


		BossAi::BossAi() {

			body_component_ = nullptr;
			dir_ = 1;
			counter_ = 0;
			state_ = E_NONE;
		}

		void BossAi::Update() {

			Behave();
		}


		void BossAi::Behave() {

			switch (state_) {

			case E_ATTACK:
				Attack();
				break;

			case E_WALK:
				 Move();
				break;

			case E_IDLE:
				Stop();
				break;

			case E_JUMP:
				Attack();
				break;

			case E_RETRIEVE:
				Retrieve();
				break;

			}
		}


		void BossAi::Reset() {

			body_component_ = nullptr;
		}

		void BossAi::Init(GameObject* owner) {

			owner_ = owner;
		}

		void BossAi::UpdateProperties() {

			body_component_ = static_cast<BodyComponent*>(owner_->GetComponent(E_COMPONENT_TYPE_BODY));
			state_ = E_WALK;
		}

		void BossAi::HandleEvent(events::Event *event) {


		}

		//Ai bhaviour related

		void BossAi::Stop() {

			if (++counter_ < max_idle_) {

				body_component_->set_velocityX(0.0f);
			}
			else {

				counter_ = 0;
				dir_ *= -1;
				state_ = E_WALK;
			}
		}

		void BossAi::Move() {

			if (++counter_ < stroll_limit_) {

				body_component_->ApplyForceX(owner_->get_move_force()*dir_);
			}
			else {
				counter_ = 0;
				state_ = E_IDLE;
			}

		}

	
		void BossAi::Attack() {


		}


		void BossAi::Retrieve() {


		}


	}
}
