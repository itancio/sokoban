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
    CHECK_FALSE(soko.solved());
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

TEST_CASE("should not mutate the board when move is invalid") {
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
    CHECK_FALSE(soko.move((Sokoban::Direction)'U'));
    CHECK(soko.board() == expected);
}

TEST_CASE("should move player down onto a goal cell") {
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
    CHECK(soko.move((Sokoban::Direction)'D'));
    CHECK(soko.board() == expected);
}

TEST_CASE("should move player off of goal cell to the left") {
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
    CHECK(soko.move((Sokoban::Direction)'L'));
    CHECK(soko.board() == expected);
}

TEST_CASE("should move left then up") {
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
    CHECK(soko.move((Sokoban::Direction)'L'));
    CHECK(soko.move((Sokoban::Direction)'U'));
    CHECK(soko.board() == expected);
}

TEST_CASE("should move right then down") {
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
    CHECK(soko.move((Sokoban::Direction)'R'));
    CHECK(soko.move((Sokoban::Direction)'D'));
    CHECK(soko.board() == expected);
}

TEST_CASE("should move player and box to the right on an empty cell") {
    std::vector<std::vector<std::string>> levels = {{
        "#####",
        "#@$ #",
        "#   #",
        "#####",
    }};
    std::vector<std::string> expected = {
        "#####",
        "# @$#",
        "#   #",
        "#####",
    };
    Sokoban soko(levels);
    CHECK(soko.move((Sokoban::Direction)'R'));
    CHECK(soko.board() == expected);
}

TEST_CASE("should move player and box-on-goal to the left on an empty cell") {
    std::vector<std::vector<std::string>> levels = {{
        "#####",
        "# *@#",
        "#####",
    }};
    std::vector<std::string> expected = {
        "#####",
        "#$+ #",
        "#####",
    };
    Sokoban soko(levels);
    CHECK(soko.move((Sokoban::Direction)'L'));
    CHECK(soko.board() == expected);
}

TEST_CASE("should move player-on-goal and box-on-goal up on an empty cell") {
    std::vector<std::vector<std::string>> levels = {{
        "###",
        "# #",
        "#*#",
        "#+#",
        "###",
    }};
    std::vector<std::string> expected = {
        "###",
        "#$#",
        "#+#",
        "#.#",
        "###",
    };
    Sokoban soko(levels);
    soko.move((Sokoban::Direction) 'U');
    CHECK(soko.board() == expected);
}

TEST_CASE("should move player-on-goal and box-on-goal down on a goal") {
    std::vector<std::vector<std::string>> levels = {{
        "###",
        "#+#",
        "#*#",
        "#.#",
        "###",
    }};
    std::vector<std::string> expected = {
        "###",
        "#.#",
        "#+#",
        "#*#",
        "###",
    };
    Sokoban soko(levels);
    soko.move((Sokoban::Direction)'D');
    CHECK(soko.board() == expected);
}

TEST_CASE("should not mutate the board when move is invalid") {
    std::vector<std::vector<std::string>> levels = {{
        "####",
        "#+$#",
        "####",
    }};

    std::vector<std::string> expected = {
        "####",
        "#+$#",
        "####",
    };
    Sokoban soko(levels);
    CHECK_FALSE(soko.move((Sokoban::Direction)'R'));
    CHECK(soko.board() == expected);
}

TEST_CASE("should not mutate the board when move is invalid") {
    std::vector<std::vector<std::string>> levels = {{
        "###",
        "#@#",
        "#$#",
        "#$#",
        "###",
    }};

    std::vector<std::string> expected = {
        "###",
        "#@#",
        "#$#",
        "#$#",
        "###",
    };
    Sokoban soko(levels);
    CHECK_FALSE(soko.move((Sokoban::Direction)'D'));
    CHECK(soko.board() == expected);
}

TEST_CASE("should move box to a goal with Left-Up sequence") {
    std::vector<std::vector<std::string>> levels = {{
        "####",
        "#. #",
        "#$ #",
        "# @#",
        "####",
    }};

    std::vector<std::string> expected = {
        "####",
        "#* #",
        "#@ #",
        "#  #",
        "####",
    };
    Sokoban soko(levels);
    CHECK(soko.move((Sokoban::Direction)'L'));
    CHECK(soko.move((Sokoban::Direction)'U'));
    CHECK(soko.board() == expected);
}

TEST_CASE("should move box to a goal with Down-Right sequence") {
    std::vector<std::vector<std::string>> levels = {{
        "#####",
        "#@  #",
        "# $.#",
        "#####",
    }};

    std::vector<std::string> expected = {
        "#####",
        "#   #",
        "# @*#",
        "#####",
    };
    Sokoban soko(levels);
    CHECK(soko.move((Sokoban::Direction)'D'));
    CHECK(soko.move((Sokoban::Direction)'R'));
    CHECK(soko.board() == expected);
}

/**** BEGIN TESTS FOR UNDO **************/

TEST_CASE("should move player down onto a goal cell, then revert to original") {
    std::vector<std::vector<std::string>> levels = {{
        "#####",
        "# @ #",
        "# . #",
        "#####",
    }};
    std::vector<std::string> expected = {
        "#####",
        "# @ #",
        "# . #",
        "#####",
    };
    Sokoban soko(levels);
    CHECK(soko.move((Sokoban::Direction)'D'));
    CHECK(soko.undo());
    CHECK(soko.board() == expected);
}

TEST_CASE("should move player off of goal cell to the left, then revert to original") {
    std::vector<std::vector<std::string>> levels = {{
        "#####",
        "#  +#",
        "#####",
    }};
    std::vector<std::string> expected = {
        "#####",
        "#  +#",
        "#####",
    };
    Sokoban soko(levels);
    CHECK(soko.move((Sokoban::Direction)'L'));
    CHECK(soko.undo());
    CHECK(soko.board() == expected);
}

TEST_CASE("should move left then up, then revert to original") {
    std::vector<std::vector<std::string>> levels = {{
        "####",
        "#  #",
        "# @#",
        "####",
    }};
    std::vector<std::string> expected = {
        "####",
        "#  #",
        "# @#",
        "####",
    };
    Sokoban soko(levels);
    CHECK(soko.move((Sokoban::Direction)'L'));
    CHECK(soko.move((Sokoban::Direction)'U'));
    CHECK(soko.undo());
    CHECK(soko.undo());
    CHECK(soko.board() == expected);
}

TEST_CASE("should move right then down, then revert to original") {
    std::vector<std::vector<std::string>> levels = {{
        "####",
        "#@ #",
        "#  #",
        "####",
    }};
    std::vector<std::string> expected = {
        "####",
        "# @#",
        "#  #",
        "####",
    };
    Sokoban soko(levels);
    CHECK(soko.move((Sokoban::Direction)'R'));
    CHECK(soko.move((Sokoban::Direction)'D'));
    CHECK(soko.undo());
    CHECK(soko.board() == expected);
}

TEST_CASE("should move player and box to the right on an empty cell, then revert to original") {
    std::vector<std::vector<std::string>> levels = {{
        "#####",
        "#@$ #",
        "#   #",
        "#####",
    }};
    std::vector<std::string> expected = {
        "#####",
        "#@$ #",
        "#   #",
        "#####",
    };
    Sokoban soko(levels);
    CHECK(soko.move((Sokoban::Direction)'R'));
    CHECK(soko.undo());
    CHECK(soko.board() == expected);
}

TEST_CASE("should move player and box-on-goal to the left on an empty cell, then revert to original") {
    std::vector<std::vector<std::string>> levels = {{
        "#####",
        "# *@#",
        "#####",
    }};
    std::vector<std::string> expected = {
        "#####",
        "# *@#",
        "#####",
    };
    Sokoban soko(levels);
    CHECK(soko.move((Sokoban::Direction)'L'));
    CHECK(soko.undo());
    CHECK(soko.board() == expected);
}

TEST_CASE("should move player-on-goal and box-on-goal up on an empty cell, then revert to original") {
    std::vector<std::vector<std::string>> levels = {{
        "###",
        "# #",
        "#*#",
        "#+#",
        "###",
    }};
    std::vector<std::string> expected = {
        "###",
        "# #",
        "#*#",
        "#+#",
        "###",
    };
    Sokoban soko(levels);
    CHECK(soko.move((Sokoban::Direction)'U'));
    CHECK(soko.undo());
    CHECK(soko.board() == expected);
}

TEST_CASE("should move player-on-goal and box-on-goal down on a goal, then revert to original") {
    std::vector<std::vector<std::string>> levels = {{
        "###",
        "#+#",
        "#*#",
        "#.#",
        "###",
    }};
    std::vector<std::string> expected = {
        "###",
        "#+#",
        "#*#",
        "#.#",
        "###",
    };
    Sokoban soko(levels);
    CHECK(soko.move((Sokoban::Direction)'D'));
    CHECK(soko.undo());
    CHECK(soko.board() == expected);
}

TEST_CASE("should move box to a goal with Left-Up sequence, then revert to original") {
    std::vector<std::vector<std::string>> levels = {{
        "####",
        "#. #",
        "#$ #",
        "# @#",
        "####",
    }};

    std::vector<std::string> expected = {
        "####",
        "#. #",
        "#$ #",
        "# @#",
        "####",
    };
    Sokoban soko(levels);
    CHECK(soko.move((Sokoban::Direction)'L'));
    CHECK(soko.move((Sokoban::Direction)'U'));
    CHECK(soko.undo());
    CHECK(soko.undo());
    CHECK(soko.board() == expected);
}

TEST_CASE("should move box to a goal with Down-Right sequence, then revert to original") {
    std::vector<std::vector<std::string>> levels = {{
        "#####",
        "#@  #",
        "# $.#",
        "#####",
    }};

    std::vector<std::string> expected = {
        "#####",
        "#@  #",
        "# $.#",
        "#####",
    };
    Sokoban soko(levels);
    CHECK(soko.move((Sokoban::Direction)'D'));
    CHECK(soko.move((Sokoban::Direction)'R'));
    CHECK(soko.undo());
    CHECK(soko.undo());
    CHECK(soko.board() == expected);
}

TEST_CASE("should return false for an invalid undo()") {
    std::vector<std::vector<std::string>> levels = {{
        "#####",
        "#@  #",
        "# $.#",
        "#####",
    }};

    std::vector<std::string> expected = {
        "#####",
        "#@  #",
        "# $.#",
        "#####",
    };
    Sokoban soko(levels);
    CHECK_FALSE(soko.move((Sokoban::Direction)'U'));
    CHECK_FALSE(soko.undo());
    CHECK(soko.board() == expected);
}

/**** END TESTS FOR UNDO **************/


/**** BEGIN TESTS FOR REDO **************/
TEST_CASE("should return false for an invalid redo()") {
    std::vector<std::vector<std::string>> levels = {{
        "#####",
        "#   #",
        "#@$.#",
        "#####",
    }};

    std::vector<std::string> expected = {
        "#####",
        "#@  #",
        "# $.#",
        "#####",
    };
    Sokoban soko(levels);
    CHECK(soko.move((Sokoban::Direction)'U'));
    CHECK_FALSE(soko.redo());
    CHECK(soko.board() == expected);
}

TEST_CASE("should redo the move after undo") {
    std::vector<std::vector<std::string>> levels = {{
        "#####",
        "#@  #",
        "# $.#",
        "#####",
    }};

    std::vector<std::string> expected = {
        "#####",
        "#   #",
        "#@$.#",
        "#####",
    };
    Sokoban soko(levels);
    CHECK(soko.move((Sokoban::Direction)'D'));
    CHECK(soko.undo());
    CHECK(soko.redo());
    CHECK(soko.board() == expected);
}

TEST_CASE("should return false after move-undo-move") {
    std::vector<std::vector<std::string>> levels = {{
        "######",
        "#@$. #",
        "######",
    }};

    std::vector<std::string> expected = {
        "######",
        "# @* #",
        "######",
    };
    Sokoban soko(levels);
    CHECK(soko.move((Sokoban::Direction)'R'));
    CHECK(soko.undo());
    CHECK(soko.move((Sokoban::Direction)'R'));
    CHECK_FALSE(soko.redo());
    CHECK(soko.board() == expected);
}

/**** END TESTS FOR REDO **************/