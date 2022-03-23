#include <iostream>
#include <numeric>
#include <string>
#include <vector>

#include "sokoban.hpp"

//#include <emscripten/emscripten.h>

static Sokoban soko({{
    "#######",
    "#  $ .#",
    "#@  ###",
    "#####",
}});
static std::string joined_board;

extern "C" {
void sokoban_initialize() {
    std::vector<std::vector<std::string>> levels{{
        "#######",
        "#  $ .#",
        "#@  ###",
        "#####",
    }};
    soko = {levels};
}

const char *sokoban_board_to_string() {
    auto board = soko.board();
    joined_board = std::accumulate(
        std::begin(board), std::end(board), std::string(),
        [](std::string &ss, std::string &s)
        { return ss.empty() ? s : ss + "\n" + s; }
    );
    return joined_board.c_str();
}

bool sokoban_move(char *s) {
    return soko.move((Sokoban::Direction)*s);
}

int sokoban_level() {
    return soko.level();
}
}

int main() {
    std::cout << "Hello Emscripten!\n";
}
