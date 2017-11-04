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

			for (int i = 0; i < leveldata_.size();++i) {

				GameObjectData data;
				data.Reset();
				data = leveldata_[i];
				GameObject* obj = GameobjectManager::GetInstance()->CreateGameObject();

				if (data.has_transform_) {
					//transform
					TransformComponent* trans = static_cast<TransformComponent*>(ComponentManager::GetInstance()->GetTransformComponent(obj->get_id()));
					trans->Init(obj);
					obj->AttachComponent(trans, E_COMPONENT_TYPE_TRANSFORM);

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

