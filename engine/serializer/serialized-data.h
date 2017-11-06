#ifndef _SERIALIZED_DATA_H_
#define _SERIALIZED_DATA_H_
#include <string>
#include <vector>

typedef struct GameObjectData {
	std::string object_name_;
	bool has_transform_;
	float pos_x_;
	float pos_y_;
	bool has_sprite_;
	std::string file_name_;
	bool is_visible_;
	bool has_controller_;
	bool has_animation_;
	float limit_;
	float step_;
	std::string direction_;

	void Reset() {

		object_name_ = "";
		has_transform_ = false;
		pos_x_ = 0.0f;
		pos_y_ = 0.0f;
		has_sprite_ = false;
		file_name_ = "";
		is_visible_ = true;
		has_controller_ = false;
		has_animation_ = false;
		limit_ = 0.0f;
		step_ = 0.0f;
		direction_ = "y";
	}

}GameObjectData;
	//std::vector<std::string> scripts_;


#endif // !_SERIALIZED_DATA_H_
