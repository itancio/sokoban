#include "sokoban.hpp"

Sokoban::Sokoban(std::vector<std::vector<std::string>> levels) {
    levels = {{
        "#####",
        "#@$.#",
        "#####",

    }};
    //this->levels = levels;
    _board = levels.at(0);

}

unsigned int Sokoban::level() {
    return current_level;
}

std::vector<std::string> Sokoban::board() {
    return _board;
}


