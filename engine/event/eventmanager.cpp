
/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: eventmanager.cpp
Purpose: manages event handling
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 16th October 2017
---------------------------------------------------------*/



#include "eventmanager.h"
#include "../common/macros.h"

#ifdef TEST_MODE
#include "../enginelogger/enginelogger.h"
#endif // !TEST_MODE

#include "../components/gameobjectmanager.h"
#include <algorithm> 

#include "event.h"
namespace enginecore {

	namespace events {

		EventManager* EventManager::instance_ = nullptr;

		EventManager* EventManager::GetInstance() {

			if (!EventManager::instance_) {

				EventManager::instance_ = new EventManager();
			}
			
			return EventManager::instance_;
		}

		void EventManager::Destroy() {


			components_subscribors_.clear();
			gameobjects_subscribers_.clear();
#ifdef TEST_MODE
			ENGINE_LOG("Destroying EventManager");
#endif // !TEST_MODE
			CLEAN_DELETE(EventManager::instance_);
		}

		void EventManager::SendEvent(Event * event) {

			Event ev = *event;

			//memcpy(&ev, event, sizeof(event));
			broadcast_event_cast_queue_.push_back(ev);
			//BroadCastToSubscribers(ev);
		}

		void EventManager::AddToQueue(Event ev, component::MainComponent * component){

			BroadCastData bd;

			bd.event_ = ev;
			//memcpy(&bd.event_, &ev, sizeof(ev));
			bd.component_ = component;

			broad_cast_queue_.push_back(bd);
		}

		void EventManager::SubscribeComponentToEvent(EventType type, component::MainComponent * component) {

			auto &list = components_subscribors_[type];
			list[component->get_id()] = component;

	
		}

		void EventManager::SubscribeGameobjectToEvent(EventType type, component::GameObject * obj) {

			auto &it = gameobjects_subscribers_[type];
			it[obj->get_id()] = obj;
	
		}

		void EventManager:: UnscribeThisComponent(EventType type, component::MainComponent* component) {

			auto &list = components_subscribors_[type];
	
			auto it = list.find(component->get_id());
			if (it != list.end()) {

				list.erase(it);
			}
		}


		void  EventManager::UnscribeThisGameObject(EventType type, component::GameObject* obj) {


			auto &list = gameobjects_subscribers_[type];

			auto it = list.find(obj->get_id());
			if (it != list.end()) {

				list.erase(it);
			}
		}

		void EventManager::	SendEvent(Event* event, component::MainComponent* component) {
			/*BroadCastData bd;
			bd.component_ = component;
			bd.event_*/
			//BroadCastToSubscribers(event);
			AddToQueue(*event, component);
		}

		void EventManager::AddTimedEvent(Event*ev ){

			//use templates here
		
			timed_events_.push_back(ev);
		}

		void EventManager:: AddTimedEvent(EventType type, float time) {

			Event* te = nullptr;

			if (type == E_EVENT_TIMEDEVENT) {

				te = new Event;
				te->set_type(E_EVENT_TIMEDEVENT);
				te->set_time(time);
			}
			if(te)
			timed_events_.push_back(te);
		}

		void EventManager::Update(float dt){

			auto itb = timed_events_.begin();
			auto ite = timed_events_.end();

			while(itb!=ite) {

				float t = (*itb)->get_time();

				t = t - dt;
				(*itb)->set_time(t);
				if (t <= 0) {

					auto itt = itb;
					itt++;
					SendEvent(*itb);
					delete *itb;
					timed_events_.erase(itb);
					itb = itt;
				}
				else {
					++itb;
				}
				
			}



			for (unsigned int i = 0; i < broad_cast_queue_.size(); i++) {

				broad_cast_queue_[i].component_->HandleEvent(&broad_cast_queue_[i].event_);
			}

				broad_cast_queue_.clear();



			for (unsigned int i = 0; i < broadcast_event_cast_queue_.size(); i++) {

				BroadCastToSubscribers(&broadcast_event_cast_queue_[i]);
			}
		/*	for (auto bd : broadcast_event_cast_queue_) {

				BroadCastToSubscribers(&bd);
			}*/
			broadcast_event_cast_queue_.clear();


		}

		void EventManager::BroadCast(Event* event) {

			//for (auto &it : broad_cast_queue_) {

				component::GameobjectManager::GetInstance()->BroadCastEvent(event);
			//}
		}
	

		void EventManager::Reset() {

			queue_event_for_components_.clear();
			broadcast_event_cast_queue_.clear();
			broad_cast_queue_.clear();///boardcast to all gamobjects
			components_subscribors_.clear();
			gameobjects_subscribers_.clear();
			std::list<Event*> timed_events_;

			auto its = timed_events_.begin();
			while (its != timed_events_.end()) {

				auto itt = its;
				itt++;
				delete *its;
				timed_events_.erase(its);
				its = itt;
			}
		}

		void EventManager::BroadCastToSubscribers(Event* event) {

			auto it = components_subscribors_.find(event->get_type());

			if (it!= components_subscribors_.end()) {

				std::unordered_map<int , component::MainComponent*> subscribers = it->second;

				for (auto& curr_component : subscribers) {

					curr_component.second->HandleEvent(event);
				}

			}

			auto it1 = gameobjects_subscribers_.find(event->get_type());

			if (it1 != gameobjects_subscribers_.end()) {

 				std::unordered_map<int ,component::GameObject*> subscribers = it1->second;

				for (auto& curr_obj : subscribers) {

					curr_obj.second->HandleEvent(event);
				}

			}
		}


	}
}