#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../../src/sokoban.hpp"

TEST_CASE("returns the board") {
    std::vector<std::vector<std::string>> levels = {{
        "#####",
        "#@$.#",
        "#####",
    }};
    Sokoban soko(levels);
    CHECK(soko.board() == levels.at(0));
}