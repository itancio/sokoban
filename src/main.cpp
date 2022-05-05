#include <exception>
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
    /* Read files from directory */
    const std::string source_path = "src/assets/levels";
    std::filesystem::path levels_dir = std::filesystem::directory_entry(source_path);

    for (const auto& entry : std::filesystem::directory_iterator(levels_dir)) {
        std::ifstream open_map_file(entry.path());
        std::string line;
        std::vector<std::string> level;

        if(!open_map_file) {
            throw "Cannot open file";
        }

        std::regex valid_elems("[#@$*.+]+");
        while (std::getline(open_map_file, line)) {
            if (std::regex_search(line, valid_elems)) {
                level.push_back(line);
            }
            else if (!level.empty()) {
                break;
            }
        }
        levels.push_back(level);
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

