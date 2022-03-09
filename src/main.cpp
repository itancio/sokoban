#include <iostream>
#include <numeric>
#include <string>
#include <vector>

#include "sokoban.hpp"

//#include <emscripten/emscripten.h>

/* this file is the interface for JS */

extern "C" {
const char *board_to_string() {
    std::vector<std::vector<std::string>> levels = {{
        "#####",
        "#@$.#",
        "#####",
    }};
    Sokoban soko(levels);
    auto board = soko.board();
    std::string s = std::accumulate(
        std::begin(board), std::end(board), std::string(),
            [](std::string &ss, std::string &s)
            {
                return ss.empty() ? s : ss + "n/" + s;
            });
    return s.c_str();
}
}

int main() {
   std::cout << "Hello Emscripten!\n";
}
