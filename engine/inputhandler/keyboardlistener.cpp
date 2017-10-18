#include "keyboardlistener.h"
#include "keyboardeventdispatcher.h"


#ifdef TEST_MODE
	#include "../enginelogger/enginelogger.h"
#endif // TEST_MODE

namespace enginecore {

	namespace inputhandler {

		KeyboardListener::KeyboardListener() {

			id_ = KeyboardEventDispatcher::GetInstance()->Register(this);

#ifdef TEST_MODE
			ENGINE_LOG("Creating KeyboardListener :%d", id_);
#endif // TEST_MODE
		}

		KeyboardListener* KeyboardListener::CreateListener() {

			KeyboardListener* listener = new KeyboardListener();
			return listener;
		}

		KeyboardListener::~KeyboardListener() {
#ifdef TEST_MODE
			ENGINE_LOG("Deleting KeyboardListener :%d",id_);
#endif // TEST_MODE
		}
	}
}

