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

TEST_CASE("should return the current level") {
    std::vector<std::vector<std::string>> levels = {{
        "#####",
        "#@$.#",
        "#####",
    }};
    Sokoban soko(levels);
    CHECK(soko.level() == 0);
}

TEST_CASE("should be solved when all boxes are on goals") {
    std::vector<std::vector<std::string>> levels = {{
        "#####",
        "# @*#",
        "#####",
    }};
    Sokoban soko(levels);
    CHECK(soko.solved());
}

TEST_CASE("should not be solved when player is on goal") {
    std::vector<std::vector<std::string>> levels = {{
        "#####",
        "#$ +#",
        "#####",
    }};
    Sokoban soko(levels);
    CHECK(!soko.solved());
}

TEST_CASE("should not be solved when empty goal cell is present") {
    std::vector<std::vector<std::string>> levels = {{
        "#####",
        "#@$.#",
        "#####",
    }};
    Sokoban soko(levels);
    CHECK(!soko.solved());
}