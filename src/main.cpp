#include <iostream>
#include <numeric>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>

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
    /*levels = {
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
    soko = {levels};*/
    //std::vector <std::vector<std::string>> levels;
    std::filesystem::path getLevelsDir = std::filesystem::directory_entry("dist/levels");
    std::vector<std::filesystem::path> getMapPath; // save path into vector element

    for (const auto& entry : std::filesystem::directory_iterator(getLevelsDir)) {
        getMapPath.push_back(entry.path());
    }

    // removes every other instance of a file found in the directory, namely the .data file since they are every other in the directory, to leave only .txt files in the vector
    for (unsigned int i = 0; i < getMapPath.size(); i++) {
        getMapPath.erase(getMapPath.begin() + i);
    }

    // opening map files stored in vector directory
    for (unsigned int i = 0; i < getMapPath.size(); i++) {
        std::ifstream openMapFile(getMapPath[i].c_str());
        std::string store_line;
        std::vector<std::string> storeMap;

        if (!openMapFile) {
            std::cerr << "Cannot open the File : " << getMapPath[i] << std::endl;
        }

        for (unsigned int i = 0; i < 1; i++) {
            while (std::getline(openMapFile, store_line)) {
                if (store_line.find("#") == false || store_line.find(" ") == false) {
                    storeMap.push_back(store_line);
                }
            }
            levels.push_back(storeMap);
        }
    };

    soko = { levels };
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

