#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_


namespace enginecore {

	namespace common {

		class SceneManager
		{
		public:
			static SceneManager* GetInstance();

			void Destroy();
			void RestartScene();
			void ResetManagers();
		private:
			SceneManager()=default;
			~SceneManager()=default;

		private:
			static SceneManager* instance_;
		};

	}

}
#endif