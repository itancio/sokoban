#include "sokoban.hpp"

#include <iostream>
#include <stdexcept>

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
            if (cell == Cell::GOAL || 
                cell == Cell::PLAYER_ON_GOAL) {
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
            if (_board[y][x] == Cell::PLAYER || 
                _board[y][x] == Cell::PLAYER_ON_GOAL) {
                px = x;
                py = y;
                return;
            }
        }
    }
    throw std::invalid_argument("Player not found...");
}

void Sokoban::move_player(int dy, int dx) {
    char current_cell = (_board[py][px] == Cell::PLAYER_ON_GOAL) ? 
        Cell::GOAL : Cell::EMPTY;
    char next_cell = (_board[py+dy][px+dx] == Cell::GOAL) ? 
        Cell::PLAYER_ON_GOAL : Cell::PLAYER;

    _board[py][px] = current_cell;
    _board[py+dy][px+dx] = next_cell;
    py += dy;
    px += dx;
}

void Sokoban::push_box(int dy, int dx) {
    // Set the box's new and old cells
    _board[py+dy][px+dx] = (_board[py+dy][px+dx] == Cell::BOX_ON_GOAL) ? 
        Cell::GOAL : Cell::EMPTY;
    _board[py+dy+dy][px+dx+dx] = (_board[py+dy+dy][px+dx+dx] == Cell::GOAL) ? 
        Cell::BOX_ON_GOAL : Cell::BOX;
}

void Sokoban::pull_box(int dy, int dx) {
    // Set the box's new and old cells
    _board[py-dy-dy][px-dx-dx] = (_board[py-dy-dy][px-dx-dx] == Cell::BOX_ON_GOAL) ? 
        Cell::GOAL : Cell::EMPTY;
    _board[py-dy][px-dx] = (_board[py-dy][px-dx] == Cell::GOAL) ? 
        Cell::BOX_ON_GOAL : Cell::BOX;
}

bool Sokoban::make_move(Direction direction) {
    std::vector<int> offsets = dir_offset[direction];
    int dy = offsets[0];
    int dx = offsets[1];
    
    // Player moves to a goal or empty cell
    if (_board[py+dy][px+dx] == Cell::GOAL || 
        _board[py+dy][px+dx] == Cell::EMPTY) {

        move_player(dy, dx);

        // Update moves sequence
        moves.push_back(direction);

        return true;
    }

    // Player encounters a box or box on goal
    if (_board[py+dy][px+dx] == Cell::BOX ||
        _board[py+dy][px+dx] == Cell::BOX_ON_GOAL) {
        
        // If the cell next to the box is a goal or empty cell,
        // then the player can push box to that cell
        if (_board[py+dy+dy][px+dx+dx] == Cell::EMPTY ||
            _board[py+dy+dy][px+dx+dx] == Cell::GOAL) {

            push_box(dy, dx);
            move_player(dy, dx);

            // Update moves sequence
            moves.push_back(direction);

            return true;
        }
    }

    return false;
}

bool Sokoban::move(Direction direction) {
    // Clears undone when player makes new move
    undone.clear();

    return make_move(direction);
}

bool Sokoban::undo() {
    if (moves.empty()) {
        return false;
    }

    // Store the last move to undone
    undone.push_back(moves.back());

    // Invert the last move and remove it from moves
    Direction direction = opposite[moves.back()];
    moves.pop_back();
    
    int dy = dir_offset[direction][0];
    int dx = dir_offset[direction][1];

    move_player(dy, dx);
    
    // Pull box after player moves to the new cell
    if (_board[py-dy-dy][px-dx-dx] == Cell::BOX ||
        _board[py-dy-dy][px-dx-dx] == Cell::BOX_ON_GOAL) {

        pull_box(dy, dx);
        return true;
    }

    return true;
}

bool Sokoban::redo() {
    if (undone.empty()) {
        return false;
    }

    Direction direction = undone.back();
    undone.pop_back();

    return make_move(direction);
}