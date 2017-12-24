#ifndef _ENUMS_H_
#define _ENUMS_H_

#include <string>

namespace enginecore {

	namespace component {

		typedef enum {

			E_COMPONENT_TYPE_NONE = 0,
			E_COMPONENT_TYPE_BODY,
			E_COMPONENT_TYPE_SHAPE,
			E_COMPONENT_TYPE_RENDER,
			E_COMPONENT_TYPE_BUTTONS,
			E_COMPONENT_TYPE_TRANSFORM,
			E_COMPONENT_TYPE_DEBUG_DRAW,
			E_COMPONENT_TYPE_INPUT_HANDLER,
			E_COMPONENT_TYPE_ANIMATION,
			E_COMPONENT_TYPE_BODY_ANIMATION,
			E_COMPONENT_TYPE_WEAPON,
			E_COMPONENT_TYPE_MOUSE,
			E_COMPONENT_TYPE_ENEMY_AI1,
			E_COMPONENT_TYPE_ENEMY_AI2,
			E_COMPONENT_TYPE_ENEMY_BOSS,
			E_COMPONENT_TYPE_BULLET,
			E_COMPONENT_TYPE_CAMERA,
			E_COMPONENT_TYPE_HEALTH,
			E_COMPONENT_HOMMING_MISSILE
		}ComponentType;



		typedef enum {

			E_NONE,
			E_WALK,
			E_IDLE,
			E_ATTACK,
			E_JUMP,
			E_RETRIEVE,
			E_WAIT
		}EnemyState;


	}
}

namespace enginecore {

	namespace physics {

		typedef enum {

			E_BODY_TYPE_STATIC = 1,
			E_BODY_TYPE_DYNAMIC,
			E_BODY_TYPE_KINEMATIC,

		}BodyType;


		typedef enum {

			E_SHAPE_CIRCLE,
			E_SHAPE_AABB,
			E_TOTAL_SHAPES
		}ShapeType;


		BodyType get_body_type(std::string name);
		ShapeType get_shape_type(std::string name);
	}
}

namespace enginecore {

	namespace events {

		typedef enum {
			E_EVENT_NONE,
			E_EVENT_COLLISION,
			E_EVENT_PLAYERHIT,
			E_EVENT_BULLETHIT,
			E_EVENT_MISSILE_HIT,
			E_EVENT_TIMEDEVENT,
			E_MOUSE_CLICKEVENT,
			E_EVENT_ENABLE_SHOOT,
			E_EVENT_DISABLE_OBJECT,
			E_EVENT_RELOAD_OBJECT,
			E_RELOAD_DONE,
			E_RELOAD,
			E_EVENT_HEALTH_HIT,
			E_BLINK_EVENT,
			E_PLAYER_DEATH,
			E_BOSS_DEATH,
			E_EVENT_DETATCH,
			E_ENABLE_JUMP,
			E_BUTTON_CLICK_EVENT,
			E_NEXT_LEVEL,
			E_GAMEOVER,
			E_RESTART,
			E_GAMEWIN,
			E_MAINMENU


		}EventType;

		EventType get_event_type(std::string name);
		
	}
}


#endif // !_ENUMS_H_
