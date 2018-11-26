#include "window.h"

namespace windowutils {
	extern const std::string window_title = "TicTacToe";
	extern const int width = 640;
	extern const int height = 480;
}

std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> Window::window
= std::unique_ptr<SDL_Window, void(*)(SDL_Window*)>(nullptr, SDL_DestroyWindow);

void Window::Init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		throw std::runtime_error("Failed to initialize SDL");

	window.reset(SDL_CreateWindow(windowutils::window_title.c_str(),
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		windowutils::width, windowutils::height, SDL_WINDOW_SHOWN));
}

void Window::Quit() {
	SDL_Quit();
}
