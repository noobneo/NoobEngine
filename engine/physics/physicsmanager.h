#ifndef _PHYSICS_MANAGER_H_
#define _PHYSICS_MANAGER_H_


namespace enginecore {

	namespace physics {

		class PhysicsManager
		{

		public:
			static PhysicsManager* GetInstance();
			void Update();
			void Destroy();
		private:
			PhysicsManager()=default;
			~PhysicsManager() = default;
			PhysicsManager(const PhysicsManager&) = delete;
			PhysicsManager& operator=(const PhysicsManager&) = delete;

		private:

			static PhysicsManager* instance_;
		};

	}
}

#endif // !_PHYSICS_MANAGER_H_
