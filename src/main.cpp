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
        // GRIGoRusha: Shito-Krito #86
        "  #########",
        "  #   #  @#",
        " ##  .$.# #",
        " #  ##  $ #",
        "##  .$*#$##",
        "#  #$#   # ",
        "#  . .# ## ",
        "####    #  ",
        "   ######  ",
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

bool sokoban_undo() {
    return soko.undo();
}

bool sokoban_redo() {
    return soko.redo();
}

bool sokoban_goTo(unsigned int r, unsigned int c) {
    return soko.move(r, c);
}

int sokoban_level() {
    return soko.level();
}
}

int main() {
    std::cout << "Hello Emscripten!\n";
}

