#ifndef GAME_H
#define GAME_H

#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <vector>

#include "window.h"

namespace gameutils {
    const int cell_width = windowutils::width / 3;
    const int cell_height = windowutils::height / 3;
}

class Game {
public:
    enum class GameState {
        running_state,
        x_won,
        o_won,
        tie_state,
        quit_state
    };

    Game();
    void OnInput(SDL_Event* event);
    void Render();
    bool isRunning();
private:
    int GetRow(const int mouse_x);
    int GetColumn(const int mouse_y);
    void PrintBoard();

    bool HasWon(int player);
    bool WonInRows(int player);
    bool WonInColumns(int player);
    bool WonInMainDiag(int player);
    bool WonInSecDiag(int player);

    bool GameIsTied();

    void RenderGrid(SDL_Renderer* renderer, SDL_Color* color);
    void RenderBoard(SDL_Renderer* renderer);
    void DrawX(SDL_Renderer* renderer, int row, int col);
    void DrawO(SDL_Renderer* renderer, int row, int col);

    void ShowMessageBox(const std::string& msg);

    GameState game_state;
    int player;
    std::vector<int> board;

    SDL_Color x_color;
    SDL_Color o_color;
    SDL_Color grid_color;

    int row, col;
};

#endif