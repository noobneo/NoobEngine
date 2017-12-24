#ifndef _SERIALIZER_H_
#define _SERIALIZER_H_

#include "serialized-data.h"
#include "../../external/rapidjson/rapidjson.h"
#include "../../external/rapidjson/document.h"
#include <string>

namespace enginecore {

	namespace serialize {

	
		class Serializer
		{

		public:

			static Serializer* GetInstance();
			void Destroy();

			EngineConfigData SerializeEngineData(std::string filename);

			void SerializeGameData(std::string filename);

#ifdef TEST_MODE
			void OutputContent(rapidjson::Value::ConstMemberIterator itr);
#endif // TEST_MODE

		private:
			Serializer() = default;
			~Serializer() = default;

			void SerializeFromJson(std::string filename, std::vector<GameObjectData> &gamedata,bool is_achetype = false);

		private:
			static Serializer* instance_;

		};

	}

}

#endif // ! _SERIALIZER_H_
