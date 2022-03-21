#include "sokoban.hpp"

#include <iostream>
#include <map>
#include <stdexcept>

Sokoban::Sokoban(std::vector<std::vector<std::string>> levels) {
    this->levels = levels;
    current_level = 0;
    steps = 0;
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
            if (cell == Sokoban::Cell::GOAL || 
                cell == Sokoban::Cell::PLAYER_ON_GOAL) {
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
            if (_board[y][x] == Sokoban::Cell::PLAYER || 
                _board[y][x] == Sokoban::Cell::PLAYER_ON_GOAL) {
                px = x;
                py = y;
                return;
            }
        }
    }
    throw std::invalid_argument("Player not found...");
}

void Sokoban::move_player(int dy, int dx) {
    char current_cell = (_board[py][px] == Sokoban::Cell::PLAYER_ON_GOAL) ? 
        Sokoban::Cell::GOAL : Sokoban::Cell::EMPTY;
    char next_cell = (_board[py+dy][px+dx] == Sokoban::Cell::GOAL) ? 
        Sokoban::Cell::PLAYER_ON_GOAL : Sokoban::Cell::PLAYER;

    _board[py][px] = current_cell;
    _board[py+dy][px+dx] = next_cell;
    py += dy;
    px += dx;
}

void Sokoban::push_box(int dy, int dx) {
    // Set the box's new and old cells
    _board[py+dy][px+dx] = (_board[py+dy][px+dx] == Sokoban::Cell::BOX_ON_GOAL) ? 
        Sokoban::Cell::GOAL : Sokoban::Cell::EMPTY;
    _board[py+dy+dy][px+dx+dx] = (_board[py+dy+dy][px+dx+dx] == Sokoban::Cell::GOAL) ? 
        Sokoban::Cell::BOX_ON_GOAL : Sokoban::Cell::BOX;
}

void Sokoban::pull_box(int dy, int dx) {
    // Set the box's new and old cells
    _board[py-dy-dy][px-dx-dx] = (_board[py-dy-dy][px-dx-dx] == Sokoban::Cell::BOX_ON_GOAL) ? 
        Sokoban::Cell::GOAL : Sokoban::Cell::EMPTY;
    _board[py-dy][px-dx] = (_board[py-dy][px-dx] == Sokoban::Cell::GOAL) ? 
        Sokoban::Cell::BOX_ON_GOAL : Sokoban::Cell::BOX;
}

bool Sokoban::make_move(Direction direction) {
    std::vector<int> offsets = dir_offset[direction];
    int dy = offsets[0];
    int dx = offsets[1];
    
    // Player moves to a goal or empty cell
    if (_board[py+dy][px+dx] == Sokoban::Cell::GOAL || 
        _board[py+dy][px+dx] == Sokoban::Cell::EMPTY) {

        move_player(dy, dx);

        // Update stats
        moves.push_back(direction);
        steps += 1; 

        return true;
    }

    // Player encounters a box or box on goal
    if (_board[py+dy][px+dx] == Sokoban::Cell::BOX ||
        _board[py+dy][px+dx] == Sokoban::Cell::BOX_ON_GOAL) {
        
        // If the cell next to the box is a goal or empty cell,
        // then the player can push box to that cell
        if (_board[py+dy+dy][px+dx+dx] == Sokoban::Cell::EMPTY ||
            _board[py+dy+dy][px+dx+dx] == Sokoban::Cell::GOAL) {

            push_box(dy, dx);
            move_player(dy, dx);

            // Update stats
            moves.push_back(direction);
            steps += 1; 

            return true;
        }
    }

    return false;
}

// Return the opposite of the given direction
Sokoban::Direction Sokoban::invert(Direction direction) {
    if (direction == Sokoban::Direction::U) {
        return Sokoban::Direction::D;
    }
    else if (direction == Sokoban::Direction::D) {
        return Sokoban::Direction::U;
    }
    else if (direction == Sokoban::Direction::L) {
        return Sokoban::Direction::R;
    }
    else if (direction == Sokoban::Direction::R) {
        return Sokoban::Direction::L;
    }
    throw std::invalid_argument("cannot invert because of invalid direction");
}

bool Sokoban::move(Direction direction) {
    // TODO: Clears every move that was undone
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
    Direction direction = invert(moves.back());
    moves.pop_back();
    
    int dy = dir_offset[direction][0];
    int dx = dir_offset[direction][1];

    move_player(dy, dx);
    
    // Pull box after player moves to the new cell
    if (_board[py-dy-dy][px-dx-dx] == Sokoban::Cell::BOX ||
        _board[py-dy-dy][px-dx-dx] == Sokoban::Cell::BOX_ON_GOAL) {

        pull_box(dy, dx);
        return true;
    }

    // Reduce steps by 1
    steps -= 1;

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

