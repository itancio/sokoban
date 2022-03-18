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

TEST_CASE("Should not mutate the board when move is invalid") {
    std::vector<std::vector<std::string>> levels = {{
        "####",
        "#@ #",
        "####",
    }};

    std::vector<std::string> expected = {
        "####",
        "#@ #",
        "####",
    };
    Sokoban soko(levels);
    CHECK_FALSE(soko.move('U'));
}

TEST_CASE("Should move player down onto a goal cell ") {
    std::vector<std::vector<std::string>> levels = {{
        "#####",
        "# @ #",
        "# . #",
        "#####",
    }};
    std::vector<std::string> expected = {
        "#####",
        "#   #",
        "# + #",
        "#####",
    };
    Sokoban soko(levels);
    CHECK(soko.move('D'));
    CHECK(soko.board() == expected);
}

TEST_CASE("Should move player off of goal cell to the left") {
    std::vector<std::vector<std::string>> levels = {{
        "#####",
        "#  +#",
        "#####",
    }};
    std::vector<std::string> expected = {
        "#####",
        "# @.#",
        "#####",
    };
    Sokoban soko(levels);
    CHECK(soko.move('l'));
    CHECK(soko.board() == expected);
}

TEST_CASE("Should move left then up") {
    std::vector<std::vector<std::string>> levels = {{
        "####",
        "#  #",
        "# @#",
        "####",
    }};
    std::vector<std::string> expected = {
        "####",
        "#@ #",
        "#  #",
        "####",
    };
    Sokoban soko(levels);
    CHECK(soko.move('l'));
    CHECK(soko.move('u'));
    CHECK(soko.board() == expected);
}

TEST_CASE("Should move right then down") {
    std::vector<std::vector<std::string>> levels = {{
        "####",
        "#@ #",
        "#  #",
        "####",
    }};
    std::vector<std::string> expected = {
        "####",
        "#  #",
        "# @#",
        "####",
    };
    Sokoban soko(levels);
    CHECK(soko.move('r'));
    CHECK(soko.move('d'));
    CHECK(soko.board() == expected);
}