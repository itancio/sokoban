#include "sokoban.hpp"

Sokoban::Sokoban(std::vector<std::vector<std::string>> levels) {
    this->levels = levels;
    current_level = 0;
    _board = levels.at(current_level);
}

unsigned int Sokoban::level() {
    return current_level;
}

bool Sokoban::solved() {
    for (std::string row : board()) {
        for (char cell : row) {
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