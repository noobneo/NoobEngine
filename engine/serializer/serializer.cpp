#include "serializer.h"


#include "../enginelogger/enginelogger.h"
#include "../common/macros.h"

#include "../components/objectfactory.h" 
#include "../../external/rapidjson/document.h"
#include "../../external/rapidjson/filereadstream.h"

//////////////////////////////////////////////////////////////////////
#include <iostream>
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>

////////////////////////////////////////////////////////////////////////


namespace enginecore {

	namespace serialize {
		
		Serializer* Serializer::instance_ = nullptr;

		Serializer* Serializer::GetInstance() {

			if (!instance_) {

				instance_ = new Serializer();
			}

			return instance_;
		}


		EngineConfigData Serializer::SerializeEngineData(std::string filename) {

			rapidjson::Document doc;

			FILE* fp;
			errno_t err;
			err = fopen_s(&fp, filename.c_str(), "rb");
			if (err != 0) {

				ENGINE_ERR_LOG("The file '%s' was not opened\n", filename.c_str());
			}

			char buffer[65233];
			rapidjson::FileReadStream fs(fp, buffer, sizeof(buffer));

			doc.ParseStream(fs);
			fclose(fp);

			EngineConfigData data;

			data.fps_ = doc["fps"].GetFloat();
			data.debug_on_ = doc["debug_on"].GetBool();
			data.texture_mode_ = doc["texture_mode"].GetBool();
			data.ptm_ = doc["ptm"].GetFloat();
			data.max_level_ = doc["max_levels"].GetInt();
			data.max_recoil_ = doc["max_recoil"].GetInt();
			data.start_scene_ = doc["start_scene"].GetString();
			data.max_objects_ = doc["max_objects"].GetInt();
			data.gravity_ = doc["gravity"].GetFloat();
			data.screen_width_ = doc["screen_width"].GetInt();
			data.screen_height_ = doc["screen_height"].GetInt();
			data.game_name_ = doc["game_name"].GetString();
			return data;
			
		}

		void Serializer::SerializeGameData(std::string filename) {

			std::vector<GameObjectData> gamedata;
		
			SerializeFromJson(filename, gamedata);

			component::ObjectFactory::GetInstance()->CreateObjectsFromGameData(gamedata);


		}

		void Serializer::SerializeFromJson(std::string filename, std::vector<GameObjectData>& gamedata, bool is_achetype ) {

			rapidjson::Document doc;

			bool is_architype = false;
			FILE* fp;
			errno_t err;
			err = fopen_s(&fp, filename.c_str(), "rb");
			if (err != 0){

				ENGINE_ERR_LOG("The file '%s' was not opened\n",filename.c_str());
			}  

			char buffer[65233];
			rapidjson::FileReadStream fs(fp, buffer, sizeof(buffer));
		
			doc.ParseStream(fs);
			fclose(fp);

			GameObjectData data;
			data.Reset();
	
			for (auto itr = doc.MemberBegin(); itr != doc.MemberEnd(); ++itr) {
#ifdef TEST_MODE
				
				OutputContent(itr);
#endif // TEST_MODE
			

				switch (itr->value.GetType()) {

				case rapidjson::Type::kArrayType:
					break;

				case rapidjson::Type::kObjectType:
				{

					std::string name(itr->name.GetString());

					if (name.find("object")!=std::string::npos) {


						auto obj = itr->value.GetObject();

						if (obj.HasMember("archetype")) {

							std::string file_name(obj["archetype"].GetString());
							SerializeFromJson(file_name, gamedata, true);

							gamedata.back().object_name_ = file_name;



							if (obj.HasMember("tag")) {

								std::string tag(obj["tag"].GetString());
								gamedata.back().tag_ = tag;
							}

							if (obj.HasMember("z_order")) {

								gamedata.back().z_order_ = obj["z_order"].GetInt();
							}

							if (obj.HasMember("mouse_component")) {

								gamedata.back().has_mouse_component_ = obj["mouse_component"].GetBool();
							}

							

							if (obj.HasMember("health")) {

								gamedata.back().has_health_ = true;
								gamedata.back().health_ = obj["health"].GetInt();
							}


							if (obj.HasMember("x")) {

								gamedata.back().pos_x_ = obj["x"].GetFloat();
							}


							if (obj.HasMember("y")) {

								gamedata.back().pos_y_ = obj["y"].GetFloat();
							}

							if (obj.HasMember("controller")) {
								gamedata.back().has_controller_ = obj["controller"].GetBool();
							}

							if (obj.HasMember("has_body")) {
								gamedata.back().has_body_ = obj["has_body"].GetBool();
							}

							if (obj.HasMember("camera")) {
								gamedata.back().has_camera_ = obj["camera"].GetBool();
							}


							if (obj.HasMember("has_children")) {
								gamedata.back().has_children_ = obj["has_children"].GetBool();
							}

							if (obj.HasMember("Ai")) {

								//override ai properties
								auto ai = obj["Ai"].GetObject();

								gamedata.back().target_name_ = ai["target_name"].GetString();
							}

							if (obj.HasMember("body")) {

								auto body = obj["body"].GetObject();

								gamedata.back().has_body_ = true;
								//	gamedata.back().has_animation_ = false;
								if (body.HasMember("body_type")) {

									std::string str_temp(body["body_type"].GetString());
									gamedata.back().body_type_ = str_temp;
								}

								if (body.HasMember("collision_tag")) {
									gamedata.back().colision_tag_ = body["collision_tag"].GetInt();
								}

								if (body.HasMember("mass")) {

									gamedata.back().mass_ = body["mass"].GetFloat();
								}

								if (body.HasMember("gravity_scale")) {

									gamedata.back().gravity_scale_ = body["gravity_scale"].GetFloat();

								}

								if (body.HasMember("velocityX")) {

									gamedata.back().velocity_x_ = body["velocityX"].GetFloat();
									gamedata.back().animated_body_velocity_x_ = gamedata.back().velocity_x_;
									gamedata.back().has_animation_ = true;
								}


								if (body.HasMember("velocityY")) {

									gamedata.back().velocity_y_ = body["velocityY"].GetFloat();
									gamedata.back().animated_body_velocity_y_ = gamedata.back().velocity_y_;
									gamedata.back().has_animation_ = true;

								}

								if (body.HasMember("shape")) {

									auto shape = body["shape"].GetObject();

									std::string str_temp(shape["shape_type"].GetString());
									gamedata.back().shape_type_ = str_temp;

									if (shape.HasMember("width")) {

										gamedata.back().width_ = shape["width"].GetFloat();
									}

									if (shape.HasMember("height")) {

										gamedata.back().height_ = shape["height"].GetFloat();
									}

									if (shape.HasMember("radius")) {

										gamedata.back().radius_ = shape["radius"].GetFloat();
									}
								}
							}

							if (obj.HasMember("has_body")) {
								gamedata.back().has_body_ = obj["has_body"].GetBool();
							}


							if (obj.HasMember("direction")) {
								std::string str_temp(obj["direction"].GetString());
								gamedata.back().direction_ = str_temp;
							}

							if (obj.HasMember("camera")) {
								gamedata.back().has_camera_ = obj["camera"].GetBool();
							}


							if (obj.HasMember("move_force")) {

								gamedata.back().move_force_ = obj["move_force"].GetFloat();

							}


							if (obj.HasMember("max_speed")) {

								gamedata.back().max_speed_ = obj["max_speed"].GetFloat();
							}


							if (obj.HasMember("jump_force")) {

								gamedata.back().jump_force_ = obj["jump_force"].GetFloat();
							}

							 if (obj.HasMember("events") ) {

								auto events = obj["events"].GetObject();
								data.has_events_ = true;

								for (auto it = events.MemberBegin(); it != events.MemberEnd(); ++it) {

									std::string str_temp(it->value.GetString());
									gamedata.back().events_.push_back(events::get_event_type(str_temp));
								}

							}



							 if (obj.HasMember("button")) {

								 auto button = obj["button"].GetObject();
								 gamedata.back().has_button_ = true;

								 if (button.HasMember("file_to_open")) {
									 gamedata.back().file_to_open_ = button["file_to_open"].GetString();
								 }

							 }

							 if (obj.HasMember("sprite")) {

								 auto spritedata = obj["sprite"].GetObject();
								
									 if (spritedata.HasMember("alpha")) {
										 gamedata.back().a_ = spritedata["alpha"].GetFloat();
									 }

							 }



						}

					}else if (name.find("animation") != std::string::npos) {

						auto obj = itr->value.GetObject();

						data.has_animation_ = true;
						data.step_ = obj["step"].GetFloat();
						data.limit_ = obj["limit"].GetFloat();
						std::string str_temp(obj["direction"].GetString());
						data.direction_ = str_temp;

						if (obj.HasMember("random")) {

							data.random_ = obj["random"].GetBool();
						}

						if (obj.HasMember("random_limit")) {

							data.random_limit_ = obj["random_limit"].GetInt();
						}
					}
					else if (name.find("sprite") != std::string::npos) {

						auto obj = itr->value.GetObject();

						data.has_sprite_ = true;
						std::string str_temp(obj["spritename"].GetString());

						data.file_name_ = str_temp;

						if (obj.HasMember("anchor_x")) {

							data.anchor_x_ = obj["anchor_x"].GetFloat();
						}

						if (obj.HasMember("z_order")) {

							data.z_order_ = obj["z_order"].GetInt();
						}
							
						if (obj.HasMember("anchor_y")) {
							data.anchor_y_ = obj["anchor_y"].GetFloat();
						}

						if (obj.HasMember("smoothness")) {
							data.smoothness_ = obj["smoothness"].GetFloat();
						}

						
						if (obj.HasMember("is_animated_sprite")) {
							data.is_animated_sprite = obj["is_animated_sprite"].GetBool();
						}


						if (obj.HasMember("total_frames")) {
							data.total_frames_ = obj["total_frames"].GetInt();
						}


						if (obj.HasMember("animation_speed")) {
							data.set_animation_speed = obj["animation_speed"].GetInt();
						}

						if (obj.HasMember("sprite_sheet_rows")) {
							data.sprite_sheet_rows_ = obj["sprite_sheet_rows"].GetInt();
						}

						if (obj.HasMember("texture_mode")) {
							data.texture_mode_ = obj["texture_mode"].GetBool();
						}

						if (obj.HasMember("spriteframes")) {
							 auto frames = obj["spriteframes"].GetObject();

							 for (auto it = frames.MemberBegin(); it != frames.MemberEnd(); ++it) {
		
								// std::string str_temp(it->value.GetString());
								 data.sprite_frames_.push_back(it->value.GetString());
							 }
							
						}

						if (obj.HasMember("color")) {
							auto colors = obj["color"].GetObject();
							
							data.r_ = colors["r"].GetFloat();
							data.g_ = colors["g"].GetFloat();
							data.b_ = colors["b"].GetFloat();
							if (colors.HasMember("a")) {

								data.a_ = colors["a"].GetFloat();
							}
						}
						if (obj.HasMember("alpha")) {
							data.a_ = obj["alpha"].GetFloat();
						}



					} else if (name.find("events") != std::string::npos) {

						auto obj = itr->value.GetObject();
						data.has_events_ = true;

						for (auto it = obj.MemberBegin(); it != obj.MemberEnd(); ++it) {

							std::string str_temp(it->value.GetString());
							data.events_.push_back(events::get_event_type(str_temp));
						}

					}
					else if (name.find("homming_missile") != std::string::npos) {

						auto obj = itr->value.GetObject();
						data.has_homming_ = true;

						data.missile_target_name_ = obj["target_name"].GetString();

					}

					else if (name.find("button") != std::string::npos) {

						auto obj = itr->value.GetObject();
						data.has_button_ = true;

						if (obj.HasMember("file_to_open")) {
							data.file_to_open_ = obj["file_to_open"].GetString();
						}

					}



					else if (name.find("Ai") != std::string::npos) {

						auto aiobj = itr->value.GetObject();
						data.has_ai_ = true;

						if (aiobj.HasMember("type")) {

							data.enemy_type_ = aiobj["type"].GetString();
						}

						if (aiobj.HasMember("stroll_limit")) {

							data.strol_limit_ = aiobj["stroll_limit"].GetInt();
						}

						if (aiobj.HasMember("max_idle")) {

							data.max_idle_ = aiobj["max_idle"].GetInt();
						}

						if (aiobj.HasMember("target_name")) {

							data.target_name_ = aiobj["target_name"].GetString();
						}

						if (aiobj.HasMember("sensor_rangeX")) {

							data.sensor_range_x_ = aiobj["sensor_rangeX"].GetInt();
						}

						if (aiobj.HasMember("sensor_rangeY")) {

							data.sensor_range_y_ = aiobj["sensor_rangeY"].GetInt();
						}

						if (aiobj.HasMember("fire_speed")) {

							data.fire_speed_ = aiobj["fire_speed"].GetFloat();
						}

						if (aiobj.HasMember("is_air_borne")) {

							data.is_air_borne_ = aiobj["is_air_borne"].GetBool();
						}

					}

					else if (name.find("bullet") != std::string::npos) {

						data.has_bullets_ = true;
						auto obj = itr->value.GetObject();
						data.bullet_damage_ = obj["bullet_damage"].GetInt();
						data.time_out_ = obj["time_out"].GetFloat();
			
					}


					else if (name.find("weapon") != std::string::npos) {

						auto obj = itr->value.GetObject();
						data.has_weapon_ = true;

						data.reload_time_ = obj["reloadtime"].GetFloat();
						data.firerate_ = obj["firerate"].GetFloat();
						data.bullet_speed_ = obj["bullet_speed"].GetFloat();
						data.spray_rate_ = obj["spray_rate"].GetInt();
						data.damage_ = obj["damage"].GetInt();
						data.recoil_ = obj["recoil"].GetInt();
						data.magsize_ = obj["magsize"].GetInt();
						data.throw_force_ = obj["throw_force"].GetFloat();
						data.listen_mouse_ = obj["listen_mouse"].GetBool();

						if (obj.HasMember("mousecontroller")) {

							data.mousecontroller_ = obj["mousecontroller"].GetBool();
						}

						if (obj.HasMember("is_launcher")) {

							data.is_launcher_ = obj["is_launcher"].GetBool();
						}

						if (obj.HasMember("bullet")) {

							std::string file_name(obj["bullet"].GetString());
							std::vector<GameObjectData> bullets;
							SerializeFromJson(file_name, bullets, true);

							for (int i = 0; i < data.magsize_; i++) {

								data.bullets_.push_back(bullets.front());
							}
						}
						

					}
					else if (name.find("child") != std::string::npos) {

						data.has_children_ = true;
						auto obj = itr->value.GetObject();

						std::string file_name(obj["archetype"].GetString());
					

						std::vector<GameObjectData> temp;
						SerializeFromJson(file_name, temp, true);
						
						if (obj.HasMember("tag")) {

							std::string tag(obj["tag"].GetString());
							temp.back().tag_ = tag;
						}

						if (obj.HasMember("offsetX")) {
							temp.back().offsetX_ = obj["offsetX"].GetFloat();
						}

						if (obj.HasMember("offsetY")) {

							temp.back().offsetY_ = obj["offsetY"].GetFloat();
						}

						if (obj.HasMember("z_order")) {

							temp.back().z_order_ = obj["z_order"].GetInt();
						}

						if (obj.HasMember("sprite")) {

							auto sprite = obj["sprite"].GetObject();

							if (sprite.HasMember("alpha")) {

								temp.back().a_ = sprite["alpha"].GetFloat();
							}
							
						}

						data.objects_.push_back(temp.front());

			
					}

					else if (name.find("body") != std::string::npos) {

						auto obj = itr->value.GetObject();
						data.has_body_ = true;

						data.mass_ = obj["mass"].GetFloat();


						if (obj.HasMember("collision_tag")) {
							data.colision_tag_ = obj["collision_tag"].GetInt();
						}
						if (obj.HasMember("is_bullet")) {
							data.is_bullet_ = obj["is_bullet"].GetBool();
						}
						
						if (obj.HasMember("is_physics_on")) {

							data.is_physics_on_ = obj["is_physics_on"].GetBool();
						}

						if (obj.HasMember("gravity_scale")) {

							data.gravity_scale_ = obj["mass"].GetFloat();
						}

						if (obj.HasMember("velocityX")) {

							data.velocity_x_ = obj["velocityX"].GetFloat();
							data.animated_body_velocity_x_ = data.velocity_x_;
						}

						if (obj.HasMember("velocityY")) {

							data.velocity_y_ = obj["velocityY"].GetFloat();
							data.animated_body_velocity_y_ = data.velocity_y_;
						}

						std::string str_temp(obj["body_type"].GetString());
						data.body_type_ = str_temp;
						
						if (obj.HasMember("shape")) {

							auto shape_obj = obj["shape"].GetObject();
							data.has_shape_ = true;

							std::string str_temp(shape_obj["shape_type"].GetString());
							data.shape_type_ = str_temp;

							if (shape_obj.HasMember("radius")) {

								data.radius_ = shape_obj["radius"].GetFloat();
							}
							else {

								data.width_ = shape_obj["width"].GetFloat();
								data.height_ = shape_obj["height"].GetFloat();
							}
						}

					}else {

							auto obj = itr->value.GetObject();
							for (auto itr1 = obj.MemberBegin(); itr1 != obj.MemberEnd(); ++itr1) {
		#ifdef TEST_MODE
								OutputContent(itr1);
		#endif // TEST_MODE
							}

							data.has_transform_ = true;

							if (obj.HasMember("x")) {
								
							data.pos_x_ = obj["x"].GetFloat();
							}

							if (obj.HasMember("y")) {

								data.pos_y_ = obj["y"].GetFloat();
							}

						
							if (obj.HasMember("scale_x")) {

								data.scale_x_ = obj["scale_x"].GetFloat();
							}

							if (obj.HasMember("scale_y")) {

								data.scale_y_ = obj["scale_y"].GetFloat();
							}
					}
				}

				break;

				case rapidjson::Type::kFalseType:
				{

					if (strcmp(itr->name.GetString(), "controller") == 0) {

						data.has_controller_ = itr->value.GetBool();

					}else if (strcmp(itr->name.GetString(), "animation") == 0) {

					//	data.has_animation_ = itr->value.GetBool();
					}
					else if (strcmp(itr->name.GetString(), "mouse_component") == 0) {


						data.has_mouse_component_ = itr->value.GetBool();

					}
					else if (strcmp(itr->name.GetString(), "active") == 0) {


						data.active_ = itr->value.GetBool();

					}
					else if (strcmp(itr->name.GetString(), "camera") == 0) {


						data.has_camera_ = itr->value.GetBool();

					}
				
					else if (strcmp(itr->name.GetString(), "level_in_debug_mode") == 0) {


						gamedata.back().level_in_debug_mode_ = itr->value.GetBool();

					}
					else if (strcmp(itr->name.GetString(), "object_debug_enable") == 0) {


						data.object_debug_enable_ = itr->value.GetBool();

					}
				}
					break;

				case rapidjson::Type::kTrueType:

				{
					if (strcmp(itr->name.GetString(), "controller") == 0) {

						data.has_controller_ = itr->value.GetBool();

					}else if (strcmp(itr->name.GetString(), "animation") == 0) {

						//data.has_animation_ = itr->value.GetBool();
					}
					else if (strcmp(itr->name.GetString(), "mouse_component") == 0) {


						data.has_mouse_component_ = itr->value.GetBool();

					}
					else if (strcmp(itr->name.GetString(), "active") == 0) {


						data.active_ = itr->value.GetBool();

					}
					else if (strcmp(itr->name.GetString(), "camera") == 0) {


						data.has_camera_ = itr->value.GetBool();

					}
			
					else if (strcmp(itr->name.GetString(), "level_in_debug_mode") == 0) {


						gamedata.back().level_in_debug_mode_ = itr->value.GetBool();

					}
					else if (strcmp(itr->name.GetString(), "object_debug_enable") == 0) {


						data.object_debug_enable_ = itr->value.GetBool();

					}
				}
					break;

				case rapidjson::Type::kStringType:

					{
						ENGINE_LOG("Value asdas: %s", itr->value.GetString());

						 if(strcmp(itr->name.GetString(), "controller") == 0){

						//	data.has_controller_ = true;

						}else if (strcmp(itr->name.GetString(), "animation") == 0) {

						//	data.has_animation_ = true;
						}
						else if (strcmp(itr->name.GetString(), "tag") == 0) {

							std::string tag(itr->value.GetString());
							data.tag_ = tag;
						}
						
						
					}
					break;


				case rapidjson::Type::kNumberType:
					ENGINE_LOG("Value : %f", itr->value.GetFloat());
					if (strcmp(itr->name.GetString(), "offsetX") == 0) {
						data.offsetX_ = itr->value.GetFloat();
					}

					else if (strcmp(itr->name.GetString(), "offsetY") == 0) {

						data.offsetY_ = itr->value.GetFloat();
					}
					else if (strcmp(itr->name.GetString(), "health") == 0) {

						data.has_health_ = true;
						data.health_ = itr->value.GetInt();
					}
					break;

				}
			}

			if (is_achetype) {

				gamedata.push_back(data);
			}

		}

#ifdef TEST_MODE
		void Serializer::OutputContent(rapidjson::Value::ConstMemberIterator itr) {


			ENGINE_LOG("Name : %s", itr->name.GetString());
			switch (itr->value.GetType()) {

				case rapidjson::Type::kArrayType : 
					break;

				case rapidjson::Type::kObjectType:
				{

					auto obj = itr->value.GetObject();
					for (auto itr1 = obj.MemberBegin(); itr1 != obj.MemberEnd(); ++itr1) {
	#ifdef TEST_MODE
						OutputContent(itr1);
	#endif // TEST_MODE
					}
				}

					break;

				case rapidjson::Type::kFalseType:
					break;

				case rapidjson::Type::kTrueType:
					break;

				case rapidjson::Type::kStringType:
	
					break;


				case rapidjson::Type::kNumberType:
						ENGINE_LOG("Value : %f", itr->value.GetFloat());
					break;

			}

		}
#endif // TEST_MODE



		void Serializer::Destroy() {

#ifdef TEST_MODE
			ENGINE_LOG("Destroying Serializer");
#endif // TEST_MODE

			CLEAN_DELETE(instance_);
		}
	}

}

