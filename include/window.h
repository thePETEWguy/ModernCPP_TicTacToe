#ifndef WINDOW_H
#define WINDOW_H

#include "SDL2/SDL.h"
#include <string>
#include <memory>

namespace windowutils {
	extern const std::string window_title;
	extern const int width;
	extern const int height;
}

class Window {
public:
	Window() = default;

	static void Init();
	static void Quit();

	static void Clear();
	static void Present();
	
	static const int FPS = 60;
private:
	static std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> window;
	static std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> renderer;
};

#endif