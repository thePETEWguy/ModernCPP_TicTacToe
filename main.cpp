#include <game.h>
#include "window.h"

#include <iostream>

int main(int argc, char** argv)
{
	try {
		Window::Init();
	}
	catch (std::runtime_error &e) {
		std::cout << e.what() << std::endl;
		Window::Quit();
	}

	Game game;
	SDL_Event event;
	
	while (game.isRunning()) {
		while (SDL_PollEvent(&event)) {
			game.OnInput(&event);
		}
		game.Render();
		SDL_Delay(1000 / Window::FPS);
	}
	Window::Quit();

	return 0;
}