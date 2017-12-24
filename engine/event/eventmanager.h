#ifndef _EVENTS_MANAGER_H_
#define _EVENTS_MANAGER_H_


/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: eventmanager.h
Purpose: manages event handling
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 16th October 2017
---------------------------------------------------------*/



#include <vector>
#include <unordered_map>
#include "../components/maincomponent.h"
#include "../components/gameobject.h"
#include "event.h"

namespace enginecore {

	namespace events{




		class BroadCastData {

		public:
			BroadCastData() {}
			Event event_;
			component::MainComponent* component_;
		};


		class EventManager
		{

		public:

			static EventManager* GetInstance();
			void Reset();
			void Destroy();
			void SendEvent(Event* event);
			void AddToQueue(Event event , component::MainComponent* component);
			void SendEvent(Event* event, component::MainComponent* component);
			void SubscribeComponentToEvent(EventType type, component::MainComponent* component);
			void SubscribeGameobjectToEvent(EventType type, component::GameObject* component);
			void UnscribeThisComponent(EventType type, component::MainComponent* component);
			void UnscribeThisGameObject(EventType type, component::GameObject* obj);
			void AddTimedEvent(Event* ev);
			void AddTimedEvent(EventType type, float time);
			void Update(float dt);

			void BroadCast(Event * event);
	
		private:
			EventManager()=default;
			~EventManager() =default;
			EventManager(const EventManager&) = delete;
			EventManager& operator= (const EventManager&) = delete;

	//		void BroadCast(EventType type);
			void BroadCastToSubscribers(Event* event);

		private:
			static EventManager* instance_;
				
			std::vector<BroadCastData> broad_cast_queue_;///boardcast to all gamobjects
			std::unordered_map<EventType, std::unordered_map<int , component::MainComponent*> > components_subscribors_;
			std::unordered_map<EventType, std::unordered_map<int  , component::GameObject*> > gameobjects_subscribers_;
			std::list<Event*> timed_events_;
			std::vector<Event>broadcast_event_cast_queue_;
			std::vector<BroadCastData>queue_event_for_components_;
		};

	}
}

#endif // !_EVENTS_MANAGER_H_
