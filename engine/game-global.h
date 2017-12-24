#ifndef _GAME_GLOBAL_H_
#define _GAME_GLOBAL_H_

#include <string>

#define MAX_SIZE 200 //total number of gameobjects or other entities that could be created eg.components,particles,animation
namespace enginecore {

		class EngineConfig {

		public:
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
			static EngineConfig* config_;
		};
}

#endif // !_GAME_GLOBAL_H_

