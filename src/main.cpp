#include <filesystem>
#include <fstream>
#include <iostream>
#include <numeric>
#include <regex>
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
    std::filesystem::path getLevelsDir = std::filesystem::directory_entry("src/assets/levels");
    std::vector<std::filesystem::path> get_map_path; // save path into vector element

    for (const auto& entry : std::filesystem::directory_iterator(getLevelsDir)) {
        get_map_path.push_back(entry.path());
    }

    std::cout << "LOOK HERE: " << get_map_path.size() << std::endl;

    // opening map files stored in vector directory
    for (unsigned int i = 0; i < get_map_path.size(); i++) {
        std::ifstream openMapFile(get_map_path[i].c_str());
        std::string store_line;
        std::vector<std::string> storeMap;

        if (!openMapFile) {
            std::cerr << "Cannot open the File : " << get_map_path[i] << std::endl;
        }

        while (std::getline(openMapFile, store_line)) {
            if (std::regex_match(store_line, std::regex("[@$*.+]+[#]{2,}"))) {
                storeMap.push_back(store_line);
            }
        }
        levels.push_back(storeMap);
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

