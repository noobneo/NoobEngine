#include "mousecomponent.h"

#include "../../external/SDL2.0 Lib/include/SDL_events.h"

#include "../maths/math-common.h"
#include "transformcomponent.h"
#include "gameobject.h"
#include "../enginelogger/enginelogger.h"
#include "../inputhandler/mouselistener.h"
#include "../inputhandler/mouseeventdispatcher.h"
#include "../event/event.h"
#include "../common/macros.h"
#include "../event/eventmanager.h"

namespace enginecore {

	namespace component {

		
		void MouseComponent::Update() {

		}

		
		void MouseComponent::Init(GameObject* owner) {

			owner_ = owner;
			follow_mouse_ = true;
			RegisterForMouseEvent();
			
		}


		void MouseComponent::RegisterForMouseEvent() {

			auto listener = inputhandler::MouseEventListener::CreateListener();
			listener->mouse_event_ = FUNCTION_CALLBACK2(MouseComponent::MouseEvent, this);
		}


		void MouseComponent::MouseEvent(uint32_t type, int x, int y) {


			if (!follow_mouse_ || !active_) {

				return;
			}
			

			switch (type) {

				case SDL_MOUSEMOTION: 
				{
					float rotate;

					float x1 = owner_->get_position_x();
					float y1 = owner_->get_position_y();

					
					rotate = maths::ConvertToDegrees(maths::GetAngle((x - x1), (y - y1)));
					owner_->SetRotation(rotate);

					break;
				}
				case SDL_MOUSEBUTTONDOWN:
				{
					events::Event ms;
					ms.set_type(events::E_MOUSE_CLICKEVENT);
					ms.set_x((float)x);
					ms.set_y((float)y);

					

					events::EventManager::GetInstance()->SendEvent(&ms);
					break;
				}
			} 


		}

		MouseComponent::MouseComponent() {

			transform_ = nullptr;
			follow_mouse_ = false;
		}

		MouseComponent::~MouseComponent() {

			Reset();
		}

		void MouseComponent::Reset() {

			transform_ = nullptr;
			follow_mouse_ = false;
			active_ = false;
		}

		void MouseComponent::HandleEvent(events::Event *event) {

		}

	}
}
