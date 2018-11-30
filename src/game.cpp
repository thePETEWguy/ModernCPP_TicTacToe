#include "game.h"
#include "window.h"

#include <iostream>

Game::Game() : game_state(GameState::running_state), player(0), board(9, -1) {
}

bool Game::isRunning(){
    return game_state == GameState::running_state ? true : false;
}

void Game::Update() {
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
            const int row = GetRow(y) - 1;
            const int col = GetColumn(x);
            const int cell = 3 * row + col - 1;

            std::cout << "Player " << player + 1 << " clicked : " << event->button.x << ", " << event->button.y << std::endl;
            if (board[cell] == -1) {
                board[cell] = player + 1;

                if (HasWon(player + 1)) {
                    if (player + 1 == 1) {
                        game_state = GameState::x_won;
                        std::cout << "X has won" << std::endl;
                    }
                    else {
                        game_state = GameState::o_won;
                        std::cout << "O has won" << std::endl;
                    }
                }
                else {
                    player = (player + 1) % 2;
                }
            }
            PrintBoard();
            break;
        }
    }
    
    if (event->type == SDL_QUIT) {
        game_state = GameState::quit_state;
    }
    if (event->key.keysym.sym == SDLK_ESCAPE) {
        game_state = GameState::quit_state;
    }
}

void Game::Render() {
    Window::Clear();
    Window::Present();
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

bool Game::HasWon(int player) {
    if (WonInRows(player)) {
        return true;
    }
    if (WonInColumns(player)) {
        return true;
    }
    if (WonInMainDiag(player)) {
        return true;
    }
    if (WonInSecDiag(player)) {
        return true;
    }
    return false;
}

bool Game::WonInRows(int player) {
    for (int i = 0; i < 7; i += 3) {
        if (board[i] != -1) {
            if (board[i] == board[i + 1] && board[i + 1] == board[i + 2]) {
                return true;
            }
        }
    }
    return false;
}

bool Game::WonInColumns(int player) {
    for (int i = 0; i < 3; i++) {
        if (board[i] != -1) {
            if (board[i] == board[i + 3] && board[i + 3] == board[i + 6]){
                return true;
            }
        }
    }
    return false;
}

bool Game::WonInMainDiag(int player) {
    if (board[0] != -1) {
        if (board[0] == board[4] && board[4] == board[8]) {
            return true;
        }
    }
    return false;
}

bool Game::WonInSecDiag(int player) {
    if (board[2] != -1) {
        if (board[2] == board[4] && board[4] == board[6]) {
            return true;
        }
    }
    return false;
}