#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "../../engine/engine.h"

bool run = true;
//game start point
int main(int argc, char** argv) {


	std::cout << "Game STart Point " << std::endl;
	if (run) {

		enginecore::Engine::GetInstance();
		run = false;
	}

	return 0;
}

