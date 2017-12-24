#include "enums.h"
#include "utils\textconverter.h"

namespace enginecore {

	namespace physics {

		BodyType get_body_type(std::string name) {

			BodyType type;
			if (strcmp(utils::TextConverter::GetInstance()->GetLowerCaseFromString(name).c_str(), "static") == 0) {


				type =  E_BODY_TYPE_STATIC;

			}else if (strcmp(utils::TextConverter::GetInstance()->GetLowerCaseFromString(name).c_str(), "kinematic") == 0) {

				type =  E_BODY_TYPE_KINEMATIC;

			} else {

				type =  E_BODY_TYPE_DYNAMIC;
			}

			return type;
		}

		ShapeType get_shape_type(std::string name) {

			ShapeType type;
			if (strcmp(utils::TextConverter::GetInstance()->GetLowerCaseFromString(name).c_str(), "circle") == 0) {


				type = E_SHAPE_CIRCLE;

			}else {

				type = E_SHAPE_AABB;
			}

			return type;
		}
	}
}

namespace enginecore {

	namespace events {

		EventType get_event_type(std::string name) {

				EventType type = E_EVENT_NONE;

			if (strcmp(utils::TextConverter::GetInstance()->GetLowerCaseFromString(name).c_str(), "player_hit") == 0) {

				type = E_EVENT_PLAYERHIT;
			} else if (strcmp(utils::TextConverter::GetInstance()->GetLowerCaseFromString(name).c_str(), "collision") == 0) {
				
				type = E_EVENT_COLLISION;

			}else if (strcmp(utils::TextConverter::GetInstance()->GetLowerCaseFromString(name).c_str(), "timed_event") == 0) {

				type = E_EVENT_TIMEDEVENT;

			}
			else if (strcmp(utils::TextConverter::GetInstance()->GetLowerCaseFromString(name).c_str(), "mouse_clickevent") == 0) {

				type = E_MOUSE_CLICKEVENT;
			}

			else if (strcmp(utils::TextConverter::GetInstance()->GetLowerCaseFromString(name).c_str(), "e_game_over") == 0) {

				type = E_GAMEOVER;
			}

			else if (strcmp(utils::TextConverter::GetInstance()->GetLowerCaseFromString(name).c_str(), "e_restart") == 0) {

				type = E_RESTART;
			}

			else if (strcmp(utils::TextConverter::GetInstance()->GetLowerCaseFromString(name).c_str(), "e_mainmenu") == 0) {

				type = E_MAINMENU;

			}
			else if (strcmp(utils::TextConverter::GetInstance()->GetLowerCaseFromString(name).c_str(), "e_gamewin") == 0) {

				type = E_GAMEWIN;

			}	
			else if (strcmp(utils::TextConverter::GetInstance()->GetLowerCaseFromString(name).c_str(), "e_player_death") == 0) {

				type = E_PLAYER_DEATH;
			}

			else if (strcmp(utils::TextConverter::GetInstance()->GetLowerCaseFromString(name).c_str(), "e_next_level") == 0) {

				type = E_NEXT_LEVEL;
			}

			else if (strcmp(utils::TextConverter::GetInstance()->GetLowerCaseFromString(name).c_str(), "e_reload") == 0) {

				type = E_RELOAD;
			}

			else if (strcmp(utils::TextConverter::GetInstance()->GetLowerCaseFromString(name).c_str(), "e_reload_done") == 0) {

				type = E_RELOAD_DONE;
			}

			else if (strcmp(utils::TextConverter::GetInstance()->GetLowerCaseFromString(name).c_str(), "e_boss_death") == 0) {

				type = E_BOSS_DEATH;
			}

			return type;
		}

	}
}

