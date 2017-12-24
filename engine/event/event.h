#ifndef _EVENT_H_
#define _EVENT_H_


/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: event.h
Purpose: contains event related information
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 16th October 2017
---------------------------------------------------------*/



#include "../enums.h"
//#include "../components/gameobject.h"
//#include "../components/maincomponent.h"


namespace enginecore {


	namespace component {

		class GameObject;
		class MainComponent;
	}
}

namespace enginecore {


	namespace events {

		class Event
		{

		public:
			EventType get_type() { return type_; };
			virtual ~Event()=default;

			Event();
			Event(EventType type) : type_(type) , time_(0.0f){}

			virtual float get_time() { return time_; };
			virtual void set_time(float time) { time_ = time; };

			inline void set_object_id(int object_id) { object_id_ = object_id; };
			inline int get_object_id() { return object_id_; };

			inline void set_other(component::GameObject* other) { other_ = other; };
			inline component::GameObject* get_other() { return other_; };

			inline void set_bullet(component::GameObject* bullet) { bullet_ = bullet; };
			inline component::GameObject* get_bullet() { return bullet_; };

			
			inline void set_missile(component::GameObject* missile) { missile_ = missile; };
			inline component::GameObject* get_missile() { return missile_; };
			
			

			component::MainComponent* get_body1() { return body1_; };
			component::MainComponent* get_body2() { return body2_; };

			void set_body1(component::MainComponent* body1) { body1_ = body1; };
			void set_body2(component::MainComponent* body2) { body2_ = body2; };

			inline void set_type(EventType type) { type_ = type; };

			inline void set_x(float x) { x_ = x; };
			inline  void set_y(float y) { y_ = y; };

			inline 	float get_x() { return x_; };
			inline float get_y() { return  y_; };


			inline void set_player(component::GameObject* player) { player_ = player; };
			inline component::GameObject* get_player() { return player_; };

			inline void set_damage(int damage) { damage_ = damage; };
			inline int get_damage() { return damage_; };

			inline int get_event_id() { return event_id_; };
			inline void set_owner_id(int owner_id) { owner_id_ =owner_id; };

			inline int get_owner_id() { return owner_id_; };
		protected:
			EventType type_;


			int damage_;
			int object_id_;
			float time_;
			float x_;
			float y_;

			component::GameObject* other_;
			component::GameObject* bullet_;
			component::GameObject* missile_;

			component::MainComponent* body1_;
			component::MainComponent* body2_;

			component::GameObject* player_;
			int owner_id_;


			static int event_id_;
		};

	}
}

#endif // _EVENT_H_
