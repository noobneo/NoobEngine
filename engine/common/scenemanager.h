#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_


/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: scenemanager.h
Purpose: manages changing of scenes 
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x64 ,Windows 7
Project: CS529_ajaytanwar
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: 14th October 2017
---------------------------------------------------------*/


#include <string>
namespace enginecore {

	namespace common {

		class SceneManager
		{
		public:

			/*
			* @function : GetInstance()
			* @return: ref to static class SceneManager
			* @brief: Creates a singleton reference to SceneManager and returns it
			*/
			static SceneManager* GetInstance();

			/*
			* @function : Destroy()
			* @brief: Resets all the managers and clears all the components and gameobjects
			*/
			void Destroy();
			
			/*
			* @function : ResetAndSerializeScene()
			* @brief: Resets a levels and serializes it again
			*/
			void ResetAndSerializeScene();
			
			/*
			* @function : LoadScene(std::string path)
			* @param path is the path of the scene(json file) to be loaded
			* @brief: loads and serialized the scene
			*/
			void LoadScene(std::string path);
			
			/*
			* @function : NextLevel()
			* @brief: increments and stores next level info
			*/
			void NextLevel();
			
			/*
			* @function : LoadsLastLevel()
			* @brief: this methods loads the last level that was played
			*/
			void LoadLastLevel();


			/*setters and getters*/

			inline int get_level_no() { return levelno_; };
			inline void set_level_no(int level_no) { levelno_ = level_no; };

		private:
			SceneManager() :levelno_(1) { }
			~SceneManager()=default;

			/*
			* @function : GetLevelNoFromFileName(std::string path)
			* @param name level name
			* @return int which is the level number for the file
			* @brief: it retrieves and returns level number from the filename
			*/
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