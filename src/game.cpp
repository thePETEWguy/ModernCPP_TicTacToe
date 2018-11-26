#include "game.h"
#include "window.h"

Game::Game() : running(true) {}

bool Game::isRunning(){
    return running;
}

void Game::Update() {

}

void Game::OnInput(SDL_Event* event) {
    if (event->type == SDL_QUIT){
        running = false;
    }
    if (event->key.keysym.sym == SDLK_ESCAPE)
    running = false;
}

void Game::Render() {
    Window::Clear();

    Window::Present();
}