#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <memory>

class Game {
public:
    Game();
    void OnInput(SDL_Event* event);
    void Render();
    void Update();
    bool isRunning();
private:
    bool running;
};

#endif