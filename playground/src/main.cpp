#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "../../engine/engine.h"

//game start point
int main(int argc, char** argv) {


	std::cout << "Game STart Point " << std::endl;

	enginecore::Engine::GetInstance();

	return 0;
}

