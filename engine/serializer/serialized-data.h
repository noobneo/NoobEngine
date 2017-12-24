#ifndef _SERIALIZED_DATA_H_
#define _SERIALIZED_DATA_H_
#include <string>
#include <vector>
#include "../enums.h"



typedef struct EngineConfig {

	float fps_;
	int max_objects_;
	float ptm_;
	bool texture_mode_;
	bool debug_on_;
	int max_recoil_;
	std::string start_scene_;
	int max_level_;
	float gravity_;
	int screen_width_;
	int screen_height_;
	std::string game_name_;

}EngineConfigData;


typedef struct GameObjectData {

	float scale_x_;
	float scale_y_;
	std::string object_name_;
	std::string tag_;
	bool active_;
	bool has_transform_;
	float pos_x_;
	float pos_y_;
	bool has_sprite_;
	std::string file_name_;
	float anchor_x_;
	float anchor_y_;
	bool is_visible_;
	bool has_controller_;
	bool has_animation_;
	float limit_;
	float step_;
	std::string direction_;
	bool has_body_;
	float mass_;
	bool has_shape_;
	int colision_tag_;
	std::string shape_type_;
	std::string body_type_;
	float radius_;
	float width_;
	float height_;
	float max_speed_;
	float jump_force_;
	float move_force_; 
	float gravity_scale_;
	float velocity_x_;
	float velocity_y_;
	bool has_events_;
	bool has_weapon_;
	float firerate_;
	float bullet_speed_;
	int spray_rate_;
	int damage_;
	int recoil_;
	int magsize_;
	float throw_force_;
	bool listen_mouse_;
	bool mousecontroller_;
	std::vector<enginecore::events::EventType> events_;
	std::vector<GameObjectData> objects_;
	bool has_children_;
	float offsetX_ ;
	float offsetY_;
	bool is_physics_on_;
	bool has_mouse_component_;
	std::vector<GameObjectData> bullets_;
	bool has_bullets_;
	int bullet_damage_ ;
	float time_out_;
	bool has_camera_;
	bool has_button_;
	int spr_width_;
	int spr_height_;
	int total_frames_;
	int sprite_sheet_rows_;
	bool is_animated_sprite;
	int set_animation_speed;
	float animated_body_velocity_x_;
	float animated_body_velocity_y_;
	std::vector<std::string>sprite_frames_;

	bool level_in_debug_mode_;
	bool object_debug_enable_;

	float reload_time_;
	std::string enemy_type_;
	int strol_limit_;
	int max_idle_;
	bool has_ai_;
	int sensor_range_x_;
	int sensor_range_y_;
	std::string target_name_;
	float fire_speed_;

	float smoothness_;
	bool texture_mode_;
	bool is_launcher_;

	float r_;
	float g_;
	float b_;
	float a_;
	bool is_bullet_;
	bool is_air_borne_;
	bool animation_loaded_; 
	bool has_health_;
	int health_;
	int z_order_;
	bool random_;
	int random_limit_;

	bool has_homming_;
std::string missile_target_name_;
std::string file_to_open_;

	void Reset() {


		scale_x_ = 1.0f;
		scale_y_ = 1.0f;
		is_launcher_ = false;
		file_to_open_ = "";

		missile_target_name_ = "";
		random_ = false;
		random_limit_ = 100;
		smoothness_ = 50.0f;
		has_health_ = false;
		health_ = 100;
		z_order_ = 0;

		animation_loaded_ = false;
		animated_body_velocity_x_ = 0.0f;

		animated_body_velocity_y_ =  0.0f;
		is_bullet_ = false;
		r_=1.0f;
		g_ = 1.0f;
		b_ = 1.0f;
		a_ = 1.0f;

		fire_speed_ = 0.0f;
		has_ai_ = false;
		active_ = true;
		object_name_ = "";
		tag_ = "";
		has_transform_ = false;
		pos_x_ = 0.0f;
		pos_y_ = 0.0f;
		has_sprite_ = false;
		file_name_ = "";
		anchor_x_ = 0.5f;
		anchor_y_ = 0.5f;
		is_visible_ = true;
		has_controller_ = false;
		has_animation_ = false;
		is_air_borne_ = false;
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
		gravity_scale_ = 1.0f;
		velocity_x_ = 0.0f;
		velocity_y_ = 0.0f;
		events_.clear();
		has_events_ = false;
		has_weapon_ = false;
		colision_tag_ = 0;
		firerate_ = 1.0f;
		spray_rate_ = 1;
		damage_=1;
		recoil_=1;
		bullet_speed_ = 50.0f;
		magsize_=1;
		mousecontroller_ = false;
		objects_.clear();
		offsetX_ = 10.0f;
		offsetY_ = 10.0f;
		throw_force_ = 90.0f;
		has_children_ = false;
		is_physics_on_ = true;
		has_mouse_component_ = false;
		bullets_.clear();
		has_bullets_ = false;
		bullet_damage_ = 50;
		time_out_ = 0.0;
		has_camera_ = false;
		has_button_ = false;
		spr_width_ = 0;
		spr_height_ = 0;
		total_frames_ = 1;
		sprite_sheet_rows_ = 1;
		is_animated_sprite = false;
		set_animation_speed = 10;
		sprite_frames_.clear();

		level_in_debug_mode_ = false; 
		object_debug_enable_ = false;

		reload_time_ = 1.0f;
		enemy_type_ = "";
		strol_limit_ = 100;
		max_idle_ = 100;

		sensor_range_x_ = 10;
		sensor_range_y_ =10;
		target_name_ = "";
		listen_mouse_ = false;
		texture_mode_ = false;

		has_homming_ = false;

	}

}GameObjectData;
	//std::vector<std::string> scripts_;


#endif // !_SERIALIZED_DATA_H_
