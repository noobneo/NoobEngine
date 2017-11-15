#ifndef _SERIALIZED_DATA_H_
#define _SERIALIZED_DATA_H_
#include <string>
#include <vector>

typedef struct GameObjectData {
	std::string object_name_;
	std::string tag_;
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
	bool has_body_;
	float mass_;
	bool has_shape_;
	std::string shape_type_;
	std::string body_type_;
	float radius_;
	float width_;
	float height_;
	float max_speed_;
	float jump_force_;
	float move_force_; 

	void Reset() {

		object_name_ = "";
		tag_ = "";
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
		has_body_ = false;
		mass_ = 0.0f;
		has_shape_ = false;
		shape_type_ = "";
		body_type_ = "";
		radius_ = 0.0f;
		width_ = 0.0f;
		height_ = 0.0f;
		max_speed_ = 1000;
		jump_force_ = 2200;
		move_force_ = 100;

	}

}GameObjectData;
	//std::vector<std::string> scripts_;


#endif // !_SERIALIZED_DATA_H_
