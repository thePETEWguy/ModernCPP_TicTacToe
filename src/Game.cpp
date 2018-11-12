#include "Game.h"

namespace gameutils {
	extern const std::string window_title = "TicTacToe";
	extern const int width = 640;
	extern const int height = 480;
}

std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> Game::window
= std::unique_ptr<SDL_Window, void(*)(SDL_Window*)>(nullptr, SDL_DestroyWindow);

void Game::Init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		throw std::runtime_error("Failed to initialize SDL");

	window.reset(SDL_CreateWindow(gameutils::window_title.c_str(),
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		gameutils::width, gameutils::height, SDL_WINDOW_SHOWN));
}

void Game::Quit() {
	SDL_Quit();
}