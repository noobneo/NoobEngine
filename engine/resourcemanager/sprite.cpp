#include "sprite.h"

#ifdef TEST_MODE
#include "../enginelogger/enginelogger.h"
#endif // TEST_MODE


namespace enginecore {

	namespace resourcemanager {


		Sprite::Sprite() {

			position_x_ = 0;
			position_y_ = 0;

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
			bounding_box_.x = position_x_;
			bounding_box_.y = position_y_;
		}

		void Sprite::SetPositionX(int position_x) {

			position_x_ = position_x;
			UpdatePosition();
		}

		void Sprite::SetPositionY(int position_y) {

			position_y_ = position_y;
			UpdatePosition();
		}

	}
}
