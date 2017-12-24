#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

#include <string>
namespace enginecore {

	namespace common {

		class SceneManager
		{
		public:
			static SceneManager* GetInstance();

			void Destroy();
			//void RestartScene();
			void ResetAndSerializeScene();
			void LoadScene(std::string path);
			void NextLevel();
			void LoadLastLevel();

			inline int get_level_no() { return levelno_; };
			inline void set_level_no(int level_no) { levelno_ = level_no; };

		private:
			SceneManager() :levelno_(1) { }
			~SceneManager()=default;

			int GetLevelNoFromFileName(std::string name);
		private:
			static SceneManager* instance_;
			std::string scene_path_;
			std::string previous_scene_path_;
			int levelno_;
		};

	}

}
#endif