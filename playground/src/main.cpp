#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "../../engine/engine.h"

//game start point
int main(int argc, char** argv) {

	int a;
	std::cout << "Game STart Point " << std::endl;

	enginecore::engine::GetInstance();

	std::cin >> a;

	enginecore::engine::GetInstance()->ShutDown();

	std::cin >> a;

	return 0;
}