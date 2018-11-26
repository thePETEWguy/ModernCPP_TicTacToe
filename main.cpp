#include "Game.h"

#include <iostream>

int main(int argc, char** argv)
{
	try {
		Game::Init();
	}
	catch (std::runtime_error &e) {
		std::cout << e.what() << std::endl;
		Game::Quit();
	}

	Game::Quit();

	return 0;
}