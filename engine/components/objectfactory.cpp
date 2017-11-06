#include "objectfactory.h"

#include "../common/macros.h"
#include "../enginelogger/enginelogger.h"
#include "gameobject.h"
#include "gameobjectmanager.h"
#include "componentmanager.h"
#include "../resourcemanager/resourcemanager.h"
#include "../resourcemanager/sprite.h"
#include "transformcomponent.h"
#include "rendercomponent.h"
#include "controllercomponent.h"
#include "animationcomponent.h"

namespace enginecore {


	namespace component {

		ObjectFactory* ObjectFactory::instance_ = nullptr;

		ObjectFactory* ObjectFactory::GetInstance() {

			if (!ObjectFactory::instance_) {

				ObjectFactory::instance_ = new ObjectFactory();
			}

			return ObjectFactory::instance_;
		}


		void ObjectFactory::CreateObjects(std::vector<GameObjectData> &leveldata) {
				
			leveldata_ = leveldata;

			for (size_t i = 0; i < leveldata_.size();++i) {

				GameObjectData data;
				data.Reset();
				data = leveldata_[i];
				GameObject* obj = GameobjectManager::GetInstance()->CreateGameObject();
				if (obj) {

					if (data.has_transform_) {
						//transform
						TransformComponent* trans = static_cast<TransformComponent*>(ComponentManager::GetInstance()->GetTransformComponent(obj->get_id()));
						trans->Init(obj);
						obj->AttachComponent(trans, E_COMPONENT_TYPE_TRANSFORM);
						obj->SetPositionX(data.pos_x_);
						obj->SetPositionY(data.pos_y_);

					} 
				
					if (data.has_sprite_) {
						//Render
						RenderComponent* render = static_cast<RenderComponent*>(ComponentManager::GetInstance()->GetRenderComponent(obj->get_id()));
						render->Init(obj);
						obj->AttachComponent(render, E_COMPONENT_TYPE_RENDER);
						resourcemanager::Sprite* spr = resourcemanager::ResourceManager::GetInstance()->CreateSprite(data.file_name_);
						render->set_sprite(spr);

					} 
				
					if (data.has_controller_) {

						//Controller
						ControllerComponent* controller = static_cast<ControllerComponent*>(ComponentManager::GetInstance()->GetControllerComponent(obj->get_id()));
						controller->Init(obj);
						obj->AttachComponent(controller, E_COMPONENT_TYPE_INPUT_HANDLER);
					}

					if (data.has_animation_) {
						//animation
						AnimationComponent* animation = static_cast<AnimationComponent*>(ComponentManager::GetInstance()->GetAnimationComponent(obj->get_id()));
						animation->Init(obj);
						animation->set_limit(data.limit_);
						animation->set_step(data.step_);
						animation->set_direction(data.direction_);
						obj->AttachComponent(animation, E_COMPONENT_TYPE_ANIMATION);
					}

				}
				else {


					ENGINE_ERR_LOG("Object could not created : %s", data.object_name_.c_str());
				}
			}
		}


		void ObjectFactory::Destroy() {
#ifdef TEST_MODE
			ENGINE_LOG("Destroying the objectFactory");
#endif // TEST_MODE

			CLEAN_DELETE(ObjectFactory::instance_);
		}
	}
}

