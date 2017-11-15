#include "sprite.h"

#ifdef TEST_MODE
#include "../enginelogger/enginelogger.h"
#endif // TEST_MODE


namespace enginecore {

	namespace graphics {


		Sprite::Sprite() {

			position_x_ = 0.0f;
			position_y_ = 0.0f;

			is_dirty_ = true;
			is_visible_ = true;
		}

		Sprite::~Sprite() {

#ifdef TEST_MODE
			ENGINE_LOG("DEstroying the Sprite");
#endif // TEST_MODE

		}

		/*void Sprite::Update() {

			if (!is_dirty_) {

				return ;
			  }
		}
		*/
		void Sprite::UpdatePosition() {

			is_dirty_ = true;
			bounding_box_.x = (int)position_x_;
			bounding_box_.y = (int)position_y_;
		}


		void Sprite::SetPosition(float position_x,float position_y) {

			position_x_ = position_x;
			position_y_ = position_y;
			UpdatePosition();
		}

		void Sprite::SetPositionX(float position_x) {

			position_x_ = position_x;
			UpdatePosition();
		}

		void Sprite::SetPositionY(float position_y) {

			position_y_ = position_y;
			UpdatePosition();
		}

	}
}
