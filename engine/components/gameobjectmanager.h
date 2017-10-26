#ifndef _GAME_OBJECT_MANAGER_H_
#define _GAME_OBJECT_MANAGER_H_


namespace enginecore {

	namespace components {

	class GameobjectManager
	{
	public:
		GameobjectManager();
		~GameobjectManager();

		void Destroy();
		static GameobjectManager* GetInstance();

	private:
		
		static GameobjectManager* instance_;
		int gameobject_id_;

	};

	}
}

#endif
