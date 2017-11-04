#ifndef  _SERIALIZER_H_
#define _SERIALIZER_H_

#include "serialized-data.h"
#ifdef TEST_MODE
	#include "../../external/rapidjson/rapidjson.h"
#include "../../external/rapidjson/document.h"
#endif // TEST_MODE

#include <string>

namespace enginecore {

	namespace serialize {

		

		class Serializer
		{

		public:

			static Serializer* GetInstance();
			void Destroy();

			void SerializeGameData(std::string filename);

#ifdef TEST_MODE
			void OutputContent(rapidjson::Value::ConstMemberIterator itr);
#endif // TEST_MODE

		private:
			Serializer() = default;
			~Serializer() = default;

			void SerializeFromJson(std::string filename, std::vector<GameObjectData> &gamedata);

		private:
			static Serializer* instance_;

		};

	}

}

#endif // ! _SERIALIZER_H_
