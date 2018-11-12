#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <string>
#include <memory>

namespace gameutils {
	extern const std::string window_title;
	extern const int width;
	extern const int height;
}

class Game {
public:
	Game() = default;

	static void Init();
	static void Quit();
private:
	static std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> window;
};

#endif