#include "sprite.h"

namespace enginecore {

	namespace resourcemanager {


		Sprite::Sprite() {

			position_x_ = 0.0f;
			position_y_ = 0.0f;

			is_dirty_ = false;
			is_visible_ = true;
		}

		Sprite::~Sprite() {


		}

		void Sprite::Update() {

			if (!is_dirty_) {

				return ;
			  }
		}

		void Sprite::UpdatePosition() {

			bounding_box_.x = pos_x_;
			bounding_box_.y = pos_y_;
		}

	}
}
