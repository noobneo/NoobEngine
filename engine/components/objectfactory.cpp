/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: objectfactory.cpp
Purpose: object factory creates gameobjects
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 16th October 2017



---------------------------------------------------------*/



#include "objectfactory.h"

#include "../common/macros.h"
#include "../enginelogger/enginelogger.h"
#include "gameobject.h"
#include "gameobjectmanager.h"
#include "../resourcemanager/resourcemanager.h"
#include "../graphics/sprite.h"
#include "component-includesh.h"
#include "../physics/physicsmanager.h"
#include "../utils/textconverter.h"
#include "../physics/shape.h"
#include "../event/eventmanager.h"
#include "../game-global.h"

namespace enginecore {


	namespace component {

		ObjectFactory* ObjectFactory::instance_ = nullptr;

		ObjectFactory* ObjectFactory::GetInstance() {

			if (!ObjectFactory::instance_) {

				ObjectFactory::instance_ = new ObjectFactory();
			}

			return ObjectFactory::instance_;
		}

		void ObjectFactory::ReloadLevel() {

			std::vector<GameObject*> created_objects;
			CreateObjects(leveldata_, created_objects);
		}


		void ObjectFactory::CreateObjectsFromGameData(std::vector<GameObjectData> &leveldata) {
			
			leveldata_ = leveldata;
			std::vector<GameObject*> created_objects;
			CreateObjects(leveldata_, created_objects);
		
		}

		void ObjectFactory::CreateObjects(std::vector<GameObjectData> &leveldata, std::vector<GameObject*> &created_objects) {
				
			
			for (size_t i = 0; i < leveldata.size();++i) {

				GameObjectData data;
				data.Reset();
				data = leveldata[i];
				GameObject* obj = GameobjectManager::GetInstance()->CreateGameObject();
				if (obj) {

					obj->set_tag(data.tag_);
					obj->set_jump_force(data.jump_force_);
					obj->set_max_speed(data.max_speed_);
					obj->set_move_force(data.move_force_);
					obj->set_offset_x(data.offsetX_);
					obj->set_offset_y(data.offsetY_);


					created_objects.push_back(obj);
				}

				if (obj) {

					if (data.has_transform_) {
						//transform
						TransformComponent* trans = static_cast<TransformComponent*>(ComponentManager::GetInstance()->GetTransformComponent(obj->get_id()));
						trans->Init(obj);
						obj->AttachComponent(trans, E_COMPONENT_TYPE_TRANSFORM);
						obj->SetPositionX(data.pos_x_);
						obj->SetPositionY(data.pos_y_);
						trans->SetScaleX(data.scale_x_);
						trans->SetScaleY(data.scale_y_);

					} 

					if (data.has_body_) {

						math::Vector2D position;
						position.x_ = data.pos_x_;
						position.y_ = data.pos_y_;
						BodyComponent* body = static_cast<BodyComponent*>(ComponentManager::GetInstance()->GetBodyComponent(obj->get_id()));
						body->set_mass(data.mass_);
						body->set_is_bullet(data.is_bullet_);
						body->set_gravity_scale(data.gravity_scale_);
						body->set_position(position);
						body->set_velocityX(data.velocity_x_);
						body->set_velocityY(data.velocity_y_);
						body->set_collision_tag(data.colision_tag_);
						body->set_is_physics_on(data.is_physics_on_);	
						body->get_shape_component()->Init(obj);

				


						/*if (data.velocity_x_ || data.velocity_y_) {

							if (!data.animation_loaded_) {

								data.animation_loaded_ = true;
								BodyAnimationComponent * animation = static_cast<BodyAnimationComponent*>(ComponentManager::GetInstance()->GetBodyAnimationComponent(obj->get_id()));
								animation->Init(obj);
								animation->set_limit(data.limit_);
								animation->set_step(data.step_);
								animation->set_direction(data.direction_);
								animation->set_velocity_x(data.animated_body_velocity_x_);
								animation->set_velocity_y(data.animated_body_velocity_y_);
								obj->AttachComponent(animation, E_COMPONENT_TYPE_BODY_ANIMATION);
							}*/
						//}

						//register with physics manager

						//if (data.has_body_) {

							physics::ShapeType type = physics::get_shape_type(data.shape_type_);
							body->get_shape_component()->AddShape(type);

							physics::BodyType body_type = physics::get_body_type(data.body_type_);
							body->set_type(body_type);

							if (type== physics::E_SHAPE_CIRCLE) {

								body->get_shape_component()->SetShapeAttribs(data.radius_);
								obj->set_height(data.radius_);
								obj->set_width(data.radius_);

							}
							else {

								body->get_shape_component()->SetShapeAttribs(data.width_ , data.height_);
								obj->set_height(data.height_);
								obj->set_width(data.width_);

							}

					//	}

						body->Init(obj);
						obj->AttachComponent(body, E_COMPONENT_TYPE_BODY);
						physics::PhysicsManager::GetInstance()->AddBodyToUpdateQueue(body);

					}

					if (data.has_ai_) {

						if (strcmp("bossai", utils::TextConverter::GetInstance()->GetLowerCaseFromString(data.enemy_type_).c_str()) == 0) {

							BossAi* bossai = static_cast<BossAi*>(ComponentManager::GetInstance()->GetEnemyBossAiComponent(obj->get_id()));
							bossai->set_stroll_limit(data.strol_limit_);
							bossai->set_max_idle(data.max_idle_);
							bossai->Init(obj);
							obj->AttachComponent(bossai, E_COMPONENT_TYPE_ENEMY_BOSS);
						}
						else if (strcmp("enemyai1", utils::TextConverter::GetInstance()->GetLowerCaseFromString(data.enemy_type_).c_str()) == 0) {

							Enemy1AI* enemyai1 = static_cast<Enemy1AI*>(ComponentManager::GetInstance()->GetEnemyAi1Component(obj->get_id()));
							enemyai1->set_stroll_limit(data.strol_limit_);
							enemyai1->set_max_idle(data.max_idle_);
							enemyai1->set_sensor_range_x(data.sensor_range_x_);
							enemyai1->set_sensor_range_y(data.sensor_range_y_);
							enemyai1->set_target_name(data.target_name_);
							enemyai1->set_fire_speed(data.fire_speed_);
							enemyai1->set_is_air_borne(data.is_air_borne_);
							enemyai1->Init(obj);
							obj->AttachComponent(enemyai1, E_COMPONENT_TYPE_ENEMY_AI1);
						}
					}


				
					if (data.has_children_) {

						std::vector<GameObject*> child_objects;
						CreateObjects(data.objects_, child_objects);

						for (auto child : child_objects) {

							child->set_parent(obj);
					
							WeaponComponent* weapon = static_cast<WeaponComponent*>(child->GetComponent(E_COMPONENT_TYPE_WEAPON));
							if (weapon) {

								weapon->set_is_equipped(true);
							//	weapon->UpdateProperties();

									if (obj->GetComponent(E_COMPONENT_TYPE_ENEMY_AI1)) {

										Enemy1AI* enmy1 = static_cast<Enemy1AI*> (obj->GetComponent(E_COMPONENT_TYPE_ENEMY_AI1));
										enmy1->set_weapon(weapon);
										weapon->set_can_shoot(true);
										weapon->SetBody();
										weapon->SetAutoMode(true);
									}
									else if (obj->GetComponent(E_COMPONENT_TYPE_ENEMY_AI2)) {

									}
								}

							}
						}
					

					if (data.has_bullets_) {

						BulletComponent* bulletcomponent = static_cast<BulletComponent*>(ComponentManager::GetInstance()->GetBulletComponent(obj->get_id()));
						bulletcomponent->set_time_out(data.time_out_);
						bulletcomponent->set_damage(data.bullet_damage_);
						bulletcomponent->Init(obj);
						obj->AttachComponent(bulletcomponent, E_COMPONENT_TYPE_BULLET);
					}



					if (data.has_homming_) {

						HomingMissile* missile = static_cast<HomingMissile*>(ComponentManager::GetInstance()->GetHommingMissileComponent(obj->get_id()));
					//	missile->set_time_out(data.time_out_);
					//	missile->set_damage(data.bullet_damage_);
						missile->set_target_name(data.missile_target_name_);
						missile->Init(obj);
						obj->AttachComponent(missile, E_COMPONENT_HOMMING_MISSILE);
					}


					if (data.has_health_) {

						HealthComponent* health_component = static_cast<HealthComponent*>(ComponentManager::GetInstance()->GetHealthComponent(obj->get_id()));
						health_component->set_health(data.health_);
						health_component->Init(obj);
						obj->AttachComponent(health_component, E_COMPONENT_TYPE_HEALTH);
					}

					if (data.has_camera_) {

						CameraComponent* cameracomponent = static_cast<CameraComponent*>(ComponentManager::GetInstance()->GetCameraComponent(obj->get_id()));
						cameracomponent->Init(obj);
						obj->AttachComponent(cameracomponent, E_COMPONENT_TYPE_CAMERA);
					}


					if (data.has_sprite_) {
						//Render
						RenderComponent* render = static_cast<RenderComponent*>(ComponentManager::GetInstance()->GetRenderComponent(obj->get_id()));	
						graphics::Sprite* spr = resourcemanager::ResourceManager::GetInstance()->CreateSprite(data.file_name_);
						spr->set_anchorpoint_x(data.anchor_x_);
						spr->set_alpha(data.a_);
						spr->set_anchorpoint_y(data.anchor_y_);
						spr->set_animation_speed(data.set_animation_speed);
						spr->set_total_frames(data.total_frames_);
						spr->set_sprite_sheet_rows(data.sprite_sheet_rows_);
						spr->set_is_animated_sprite(data.is_animated_sprite);
						spr->set_smoothness(data.smoothness_);
						if (data.z_order_ != -1) {
							spr->SetZorder(data.z_order_);
						}



						spr->CreateSpriteMap(data.sprite_frames_);
						spr->set_texture_mode(data.texture_mode_ | enginecore::EngineConfig::config_->texture_mode_);
						spr->Init();
						data.spr_width_ = (int)spr->get_frame_width();
						data.spr_height_= (int)spr->get_frame_height();

						render->set_sprite(spr);
						render->Init(obj);
						obj->AttachComponent(render, E_COMPONENT_TYPE_RENDER);

					} 
				

					
					if (data.has_controller_) {

						//Controller
						ControllerComponent* controller = static_cast<ControllerComponent*>(ComponentManager::GetInstance()->GetControllerComponent(obj->get_id()));
						controller->Init(obj);
						obj->AttachComponent(controller, E_COMPONENT_TYPE_INPUT_HANDLER);
					}

					if (data.has_button_) {

						//Controller
						ButtonComponent* button = static_cast<ButtonComponent*>(ComponentManager::GetInstance()->GetButtonComponent(obj->get_id()));
						button->Init(obj);
						button->set_file_to_open(data.file_to_open_);
						obj->AttachComponent(button, E_COMPONENT_TYPE_BUTTONS);
					}

					if (data.has_weapon_) {

						//Controller
						WeaponComponent* weapon = static_cast<WeaponComponent*>(ComponentManager::GetInstance()->GetWeaponComponent(obj->get_id()));
						weapon->set_damage(data.damage_);
						weapon->set_fire_rate(data.firerate_);
						weapon->set_bullet_speed(data.bullet_speed_);
						weapon->set_spray_rate(data.spray_rate_);
						weapon->set_mag_size(data.magsize_);
						weapon->set_recoil(data.recoil_);
						weapon->set_listen_mouse(data.listen_mouse_);
						weapon->set_is_launcher(data.is_launcher_);
						weapon->set_throw_force(data.throw_force_);
						weapon->set_has_mouse_controller(data.mousecontroller_);
						weapon->set_reload_time(data.reload_time_);
						weapon->Init(obj);
						obj->AttachComponent(weapon, E_COMPONENT_TYPE_WEAPON);

						std::vector<GameObject*> bullets_objects;
						CreateObjects(data.bullets_, bullets_objects);

						for (unsigned int i = 0; i < bullets_objects.size(); i++) {

							weapon->AddBulletToPool(bullets_objects[i]);
						}

					}



					if (data.has_animation_&& !data.animation_loaded_) {
						//animation
						data.animation_loaded_ = true;
					//	data.has_animation_ = false;
						if (data.has_body_) {

							BodyAnimationComponent * animation = nullptr;
							animation = static_cast<BodyAnimationComponent*>(ComponentManager::GetInstance()->GetBodyAnimationComponent(obj->get_id()));
							animation->Init(obj);
							animation->set_limit(data.limit_);
							animation->set_step(data.step_);
							animation->set_direction(data.direction_);
							animation->set_random(data.random_);
							animation->set_random_limit(data.random_limit_);
							animation->set_velocity_x(data.animated_body_velocity_x_);
							animation->set_velocity_y(data.animated_body_velocity_y_);
							obj->AttachComponent(animation, E_COMPONENT_TYPE_BODY_ANIMATION);
						}

						else {

							AnimationComponent* animation = static_cast<AnimationComponent*>(ComponentManager::GetInstance()->GetAnimationComponent(obj->get_id()));
							animation->Init(obj);
							animation->set_limit(data.limit_);
							animation->set_step(data.step_);
							animation->set_direction(data.direction_);
							obj->AttachComponent(animation, E_COMPONENT_TYPE_ANIMATION);
						}
						
					}
					if (data.has_mouse_component_) {

						MouseComponent* mouse_component = static_cast<MouseComponent*>(ComponentManager::GetInstance()->GetMouseComponent(obj->get_id()));
						mouse_component->Init(obj);
						obj->AttachComponent(mouse_component, E_COMPONENT_TYPE_MOUSE);

					}

					if (data.has_events_) {

						for (auto it : data.events_) {
							if (it != events::E_EVENT_NONE) {

								events::EventManager::GetInstance()->SubscribeGameobjectToEvent(it , obj);
							}
						}
					}

					
						
					if(data.has_body_){
						
						BoundingBoxComponent* debug_draw = static_cast<BoundingBoxComponent*>(ComponentManager::GetInstance()->GetDebugDrawComponent(obj->get_id()));
						debug_draw->set_anchorpoint_x(data.anchor_x_);
						debug_draw->set_anchorpoint_x(data.anchor_y_);

						debug_draw->set_bound_width(data.spr_width_);
						debug_draw->set_bound_height(data.spr_height_);
						debug_draw->Init(obj);
						debug_draw->SetColor(data.r_, data.g_, data.b_,data.a_);
						obj->AttachComponent(debug_draw, E_COMPONENT_TYPE_DEBUG_DRAW);
					}

					if (obj) {

						obj->UpdateComponentProperties(data.active_);
	
					}
				}
				else {


					ENGINE_ERR_LOG("Object could not created : %s", data.object_name_.c_str());
				}
			}

		}


		void ObjectFactory::Destroy() {
#ifdef DESTRUCTOR_LOG_MODE
			ENGINE_LOG("Destroying the objectFactory");
#endif // TEST_MODE

			CLEAN_DELETE(ObjectFactory::instance_);
		}
	}
}

