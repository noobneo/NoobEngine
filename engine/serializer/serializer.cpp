#include "serializer.h"

#ifdef TEST_MODE
#include "../enginelogger/enginelogger.h"
#endif // TEST_MODE
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

		void Serializer::SerializeGameData(std::string filename) {

			std::vector<GameObjectData> gamedata;
		
			SerializeFromJson(filename, gamedata);

			component::ObjectFactory::GetInstance()->CreateObjects(gamedata);


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

						 
						std::string file_name(obj["archetype"].GetString());
						std::string tag(obj["tag"].GetString());
						SerializeFromJson(file_name, gamedata,true);
						
						gamedata.back().tag_ = tag;
						gamedata.back().object_name_ = file_name;
						gamedata.back().pos_x_ = obj["x"].GetFloat();
						gamedata.back().pos_y_ = obj["y"].GetFloat();

						if (obj.HasMember("controller")) {
							gamedata.back().has_controller_ = obj["controller"].GetBool();
						}


						if (obj.HasMember("body")) {

							auto body = obj["body"].GetObject();

							gamedata.back().has_body_ = true;
							gamedata.back().has_animation_ = false;
							if (body.HasMember("body_type")) {

								std::string str_temp(body["body_type"].GetString());
								gamedata.back().body_type_ = str_temp;
							}


							if (body.HasMember("mass")) {

								gamedata.back().mass_ = body["mass"].GetFloat();
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



							}
						}


						if (obj.HasMember("direction")) {
							std::string str_temp(obj["direction"].GetString());
							gamedata.back().direction_ = str_temp;
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



					}else if (name.find("animation") != std::string::npos) {

						auto obj = itr->value.GetObject();

						data.has_animation_ = true;
						data.step_ = obj["step"].GetFloat();
						data.limit_ = obj["limit"].GetFloat();
						std::string str_temp(obj["direction"].GetString());
						data.direction_ = str_temp;

					}
					else if (name.find("body") != std::string::npos) {

						auto obj = itr->value.GetObject();
						data.has_body_ = true;

						data.mass_ = obj["mass"].GetFloat();

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
							data.pos_x_ = obj["x"].GetFloat();
							data.pos_y_ = obj["y"].GetFloat();
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
				}
					break;

				case rapidjson::Type::kTrueType:

				{
					if (strcmp(itr->name.GetString(), "controller") == 0) {

						data.has_controller_ = itr->value.GetBool();

					}else if (strcmp(itr->name.GetString(), "animation") == 0) {

						//data.has_animation_ = itr->value.GetBool();
					}
				}
					break;

				case rapidjson::Type::kStringType:

					{
						ENGINE_LOG("Value asdas: %s", itr->value.GetString());

						if (strcmp(itr->name.GetString(), "sprite") == 0) {

							data.has_sprite_ = true;
							std::string str_temp(itr->value.GetString());

							data.file_name_ = str_temp;

						}else if(strcmp(itr->name.GetString(), "controller") == 0){

						//	data.has_controller_ = true;

						}else if (strcmp(itr->name.GetString(), "animation") == 0) {

						//	data.has_animation_ = true;
						}
						
					}
					break;


				case rapidjson::Type::kNumberType:
					ENGINE_LOG("Value : %f", itr->value.GetFloat());
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

