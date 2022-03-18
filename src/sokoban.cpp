#include "sokoban.hpp"

Sokoban::Sokoban(std::vector<std::vector<std::string>> levels) {
    this->levels = levels;
    current_level = 0;
    _board = levels.at(current_level);
    locate_player();
}

void Sokoban::print_board() {
    for (std::string &row : board()) {
        std::cout << row << '\n';
    }
}

unsigned int Sokoban::level() {
    return current_level;
}

bool Sokoban::solved() {
    for (const std::string &row : board()) {
        for (const char cell : row) {
            if (cell == '.' || cell == '+') {
                return false;
            }
        }
    }
    return true;
}

std::vector<std::string> Sokoban::board() {
    return _board;
}

void Sokoban::locate_player() {
    for (unsigned int y = 0; y < _board.size(); y++) {
        for (unsigned int x = 0; x < _board[y].size(); x++) {
            if (_board[y][x] == '@' || _board[y][x] == '+') {
                px = x;
                py = y;
                return;
            }
        }
    }
    throw std::invalid_argument("Player not found...");
}

bool Sokoban::make_move(int dy, int dx) {
    char current_cell;
    char next_cell;
    // If the player is currently on a goal cell ,'+', then moves
    // off of the goal cell, the current_cell will revert to an open cell
    // or a goal cell.
    if (_board[py][px] == '+') {
        current_cell = '.';
    }
    else {
        current_cell = ' ';
    }

    // If the player moves to a goal cell, then the next_cell
    // will change the player's state to '+',
    // if not moved to a goal cell then, '@'.
    if (_board[py+dy][px+dx] == '.') {
        next_cell = '+';
    }
    else {
        next_cell = '@';
    }

    if (_board[py+dy][px+dx] == '.' || _board[py+dy][px+dx] == ' ') {
        _board[py][px] = current_cell;
        _board[py+dy][px+dx] = next_cell;
        py += dy;
        px += dx;
        return true;
    }
    return false;
}

bool Sokoban::move(char direction) {
    direction = toupper(direction);
    if (direction == 'U') {
        return make_move(-1,0);
    }
    else if (direction == 'D') {
        return make_move(1,0);
    }
    else if (direction == 'L') {
        return make_move(0,-1);
    }
    else if (direction == 'R') {
        return make_move(0,1);
    }
    return false;
}