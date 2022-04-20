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
static std::vector<std::vector<std::string>> levels;

extern "C" {
void sokoban_initialize() {
    levels = {
        {
            // greg messing around
            "   ####",
            "####. ##",
            "#.##$ .##",
            "# ##    #",
            "#    $  #",
            "# #### ##",
            "#@ $   #",
            "#####  #",
            "    ####",
        },
        {
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
        },
        {
            "######",
            "#@ $.#",
            "######",
        },
        {
            "######",
            "#@ $.#",
            "######",
        },
        {
            "######",
            "#@ $.#",
            "######",
        },
    };
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
    return soko.move((Sokoban::Direction) *s);
}

bool sokoban_goto(int row, int col) {
    return soko.move(row, col);
}

bool sokoban_solved() {
    return soko.solved();
}

bool sokoban_undo() {
    return soko.undo();
}

bool sokoban_redo() {
    return soko.redo();
}

int sokoban_level() {
    return soko.level();
}

void sokoban_change_level(int level) {
    soko.change_level(level);
}

int sokoban_levels_size() {
    return levels.size();
}
}

int main() {
    std::cout << "Hello Emscripten!\n";
}

