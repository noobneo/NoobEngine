
#ifndef _COMPONENT_TYPES_H_
#define _COMPONENT_TYPES_H_

#define MAX_SIZE 1 //total number of gameobjects or other entities that could be created eg.components,particles,animation

typedef enum {

	E_COMPONENT_TYPE_NONE = 0,
	E_COMPONENT_TYPE_RENDER,
	E_COMPONENT_TYPE_PHYSICS,
	E_COMPONENT_TYPE_BUTTONS,
	E_COMPONENT_TYPE_TRANSFORM,
	E_COMPONENT_TYPE_DEBUG_DRAW,
	E_COMPONENT_TYPE_INPUT_HANDLER,
}ComponentType;


typedef struct GameObjectData{
	bool has_transform;
	float pos_x;
	float pos_y;
	bool has_sprite;
	bool is_visible;
	std::string file_name_;
	std::vector<std::string> scripts_;
};

#endif // !_COMPONENT_TYPES_H_
