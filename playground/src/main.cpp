#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "../../engine/engine.h"
#include "../../engine/serializer/serializer.h"

bool run = true;
//game start point
int main(int argc, char** argv) {

	std::cout << "Game STart Point " << std::endl;
	if (run) {

		enginecore::Engine::GetInstance();
		run = false;
		enginecore::serialize::Serializer::GetInstance()->SerializeGameData("playground/resources/gamedata/player.json");
		enginecore::Engine::GetInstance()->Run();
	}


	return 0;
}

