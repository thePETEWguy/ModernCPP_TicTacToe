#ifndef GAME_H
#define GAME_H

#include <memory>
#include <SDL2/SDL.h>
#include <vector>

namespace gameutils {
    const int cell_width = 640 / 3;//windowutils::width / 3;
    const int cell_height = 480 / 3;//windowutils::height / 3;
}

class Game {
public:
    enum class GameState {
        running_state,
        x_won,
        o_won,
        quit_state
    };

    Game();
    void OnInput(SDL_Event* event);
    void Render();
    void Update();
    bool isRunning();
private:
    GameState game_state;
    int player;
    std::vector<int> board;

    int GetRow(const int mouse_x);
    int GetColumn(const int mouse_y);
    void PrintBoard();

    bool HasWon(int player);
    bool WonInRows(int player);
    bool WonInColumns(int player);
    bool WonInMainDiag(int player);
    bool WonInSecDiag(int player);
};

#endif