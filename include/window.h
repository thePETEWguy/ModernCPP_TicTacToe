#ifndef WINDOW_H
#define WINDOW_H


#include <memory>
#include <string>
#include <SDL2/SDL.h>

namespace windowutils {
	extern const std::string window_title;
	extern const int width;
	extern const int height;
}

class Window {
public:
	Window() = default;
	Window(const Window& rhs) = delete;
	~Window() = default;

	static void Init();
	static void Quit();

	static void Clear();
	static void Present();

	static SDL_Renderer* GetRenderer();
	
	static const int FPS = 60;
private:
	static std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> window;
	static std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> renderer;
};

#endif