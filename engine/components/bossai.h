#ifndef _BOSSENEMYAI_COMPONENT_H_
#define _BOSSENEMYAI_COMPONENT_H_


/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: bossai.h
Purpose: boss ai component behaviour
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 16th October 2017
---------------------------------------------------------*/


#include "maincomponent.h"

#include "../enums.h"

namespace enginecore {

	namespace component {

		class GameObject;
		class Shape;
		class BodyComponent;

		class BossAi : public MainComponent
		{

		private:
			BossAi();
			~BossAi() = default;


			virtual void Update();
			virtual void Reset();
			virtual void Init(GameObject* owner);
			virtual void HandleEvent(events::Event *event);

			virtual void UpdateProperties();

			void Behave();
			void Stop();
			void Move();
			void Attack();
			void Retrieve();

		private:

			inline void set_stroll_limit(int stroll_limit) { stroll_limit_ = stroll_limit; };
			inline void set_max_idle(int max_idle) { max_idle_ = max_idle; };

		private:
			friend class ComponentManager;
			friend class ObjectFactory;

			BodyComponent* body_component_;

			bool is_idle_;

			int dir_;
			int counter_;
			int stroll_limit_;
			int max_idle_;
			EnemyState state_;

		};
	}
}

#endif //_BOSSENEMYAI_COMPONENT_H_