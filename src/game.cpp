#include "game.h"

#include <iostream>

Game::Game() : game_state(GameState::running_state), 
                          player(1), 
                          board(9, -1),
                          grid_color {.r = 255, .g = 255, .b = 255},
                          x_color {.r = 220, .g = 20, .b = 60},
                          o_color {.r = 0, .g = 0, .b = 255},
                          row(-1), col(-1) {
}

bool Game::isRunning(){
    return game_state == GameState::running_state ? true : false;
}

void Game::OnInput(SDL_Event* event) {
    switch (event->type){
        case SDL_QUIT: {
            game_state = GameState::quit_state;
            break;
        }
        case SDL_KEYDOWN: {
            switch (event->key.keysym.sym){
                case SDLK_ESCAPE: {
                    game_state = GameState::quit_state;
                    break;
                }
            }
            break;
        }
        case SDL_MOUSEBUTTONDOWN: {
            const int x = event->button.x;
            const int y = event->button.y;
            row = GetRow(y);
            col = GetColumn(x);
            const int cell = 3 * (row - 1) + col - 1;

            if (board[cell] == -1) {
                board[cell] = player;

                if (HasWon()) {
                    if (player == 1) {
                        game_state = GameState::x_won;
                    }
                    else {
                        game_state = GameState::o_won;
                    }
                }
                else if (GameIsTied()) {
                    game_state = GameState::tie_state;
                }
                player = (player == 1) ? 2 : 1;
            }
            break;
        }
    }
}

void Game::RenderGrid(SDL_Renderer* renderer, SDL_Color* color) {
    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, 255);

    for (auto i = 1; i < 3; i++) {
        SDL_RenderDrawLine(renderer,
            i * gameutils::cell_width, 0,
            i * gameutils::cell_width, windowutils::height);
        SDL_RenderDrawLine(renderer,
            0, i * gameutils::cell_height,
            windowutils::width, i * gameutils::cell_height);
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void Game::DrawX(SDL_Renderer* renderer, int row, int col) {
    int first_x1 = 10;
    int first_y1 = 10;
    int first_x2 = 200;
    int first_y2 = 150;

    int second_x1 = 200;
    int second_y1 = 10;
    int second_x2 = 10;
    int second_y2 = 150;

    int x_to_add = 0;
    int y_to_add = 0;

    if (col == 1) {
        x_to_add = gameutils::cell_width;
    }
    else if (col == 2) {
        x_to_add = gameutils::cell_width * 2;
    }

    if (row == 1) {
        y_to_add = gameutils::cell_height;
    }
    else if (row == 2) {
        y_to_add = gameutils::cell_height * 2;
    }

    thickLineRGBA(renderer, 10 + x_to_add, 10 + y_to_add, 200 + x_to_add, 150 + y_to_add, 20, x_color.r, x_color.g, x_color.b, 255);
    thickLineRGBA(renderer, 200 + x_to_add, 10 + y_to_add, 10 + x_to_add, 150 + y_to_add, 20, x_color.r, x_color.g, x_color.b, 255);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}

void Game::DrawO(SDL_Renderer* renderer, int row, int col) {
    int x_to_add = 0;
    int y_to_add = 0;

    if (col == 1) {
        x_to_add = gameutils::cell_width;
    }
    else if (col == 2) {
        x_to_add = gameutils::cell_width * 2;
    }

    if (row == 1) {
        y_to_add = gameutils::cell_height;
    }
    else if (row == 2) {
        y_to_add = gameutils::cell_height * 2;
    }

    filledCircleRGBA(renderer, x_to_add + gameutils::cell_width * 0.5, y_to_add + gameutils::cell_height * 0.5, 75, o_color.r, o_color.g, o_color.b, 255);
    filledCircleRGBA(renderer, x_to_add + gameutils::cell_width * 0.5, y_to_add + gameutils::cell_height * 0.5, 60, 0, 0, 0, 255);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}

void Game::RenderBoard(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, o_color.r, o_color.g, o_color.g, 255);    
}

void Game::Render() {
    RenderGrid(Window::GetRenderer(), &grid_color);
    RenderCurrentPlayer();
    Window::Present();
    CheckGameState();    
}

void Game::RenderCurrentPlayer() {
    if (row != -1 && col != -1) {
        if (player == 2) {  // because the player changes before rendering, we check the player "swapped"
            DrawX(Window::GetRenderer(), row - 1, col - 1);
        }
        else {
            DrawO(Window::GetRenderer(), row - 1, col - 1);
        }
    }
}

void Game::CheckGameState() {
    switch (game_state) {
        case GameState::x_won: {
            ShowMessageBox("Player1 has won the game");
            break;
        }
        case GameState::o_won: {
            ShowMessageBox("Player2 has won the game");
            break;
        }
        case GameState::tie_state: {
            ShowMessageBox("Game is tied");
            break;
        }
        default: {}
    }
}

int Game::GetRow(const int mouse_y) {
    if (mouse_y < gameutils::cell_height){
        return 1;
    }
    else if (mouse_y >= gameutils::cell_height && mouse_y < gameutils::cell_height * 2) {
        return 2;
    }
    return 3;
}

int Game::GetColumn(const int mouse_x){
    if (mouse_x < gameutils::cell_width){
        return 1;
    }
    else if (mouse_x >= gameutils::cell_width && mouse_x < gameutils::cell_width * 2) {
        return 2;
    }
    return 3;
}

void Game::PrintBoard() {
    size_t index = 1;
    for (const auto& cell : board) {
        std::cout << cell << " ";
        if (index % 3 == 0) {
            std::cout << std::endl;
        }
        index++;
    }
}

bool Game::HasWon() {
    if (WonInRows()) {
        return true;
    }
    if (WonInColumns()) {
        return true;
    }
    if (WonInMainDiag()) {
        return true;
    }
    if (WonInSecDiag()) {
        return true;
    }
    return false;
}

bool Game::WonInRows() {
    for (int i = 0; i < 7; i += 3) {
        if (board[i] != -1) {
            if (board[i] == board[i + 1] && board[i + 1] == board[i + 2]) {
                return true;
            }
        }
    }
    return false;
}

bool Game::WonInColumns() {
    for (int i = 0; i < 3; i++) {
        if (board[i] != -1) {
            if (board[i] == board[i + 3] && board[i + 3] == board[i + 6]){
                return true;
            }
        }
    }
    return false;
}

bool Game::WonInMainDiag() {
    if (board[0] != -1) {
        if (board[0] == board[4] && board[4] == board[8]) {
            return true;
        }
    }
    return false;
}

bool Game::WonInSecDiag() {
    if (board[2] != -1) {
        if (board[2] == board[4] && board[4] == board[6]) {
            return true;
        }
    }
    return false;
}

bool Game::GameIsTied() {
    for (const auto& cell : board) {
        if (cell == -1)
            return false;
    }
    return true;
}

void Game::ShowMessageBox(const std::string& msg) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "", msg.c_str(), nullptr);
}