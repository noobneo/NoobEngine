#ifndef  _SERIALIZER_H_
#define _SERIALIZER_H_

#include <string>

namespace enginecore {

	namespace serialize {

		class Serializer
		{

		public:

			static Serializer* GetInstance();
			void Destroy();

			void SerializeGameData(std::string filename);
		private:
			Serializer() = default;
			~Serializer() = default;

		private:
			static Serializer* instance_;

		};

	}

}

#endif // ! _SERIALIZER_H_
