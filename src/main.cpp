#include <filesystem>
#include <fstream>
#include <map>
#include <numeric>
#include <regex>
#include <string>
#include <vector>

#include "sokoban.hpp"

static Sokoban soko({{
    "#######",
    "#  $ .#",
    "#@  ###",
    "#####",
}});
static std::string joined_board;
static std::string sequence_str;
static std::vector<std::vector<std::string>> levels;

void read_levels(const std::string path = "src/assets/levels") {
    std::map<int, std::vector<std::string>> ordered_levels;
    std::filesystem::path levels_dir =
        std::filesystem::directory_entry(path);

    for (const auto& entry : std::filesystem::directory_iterator(levels_dir)) {
        std::ifstream level_file(entry.path());

        if (!level_file) {
            throw std::invalid_argument("Cannot open file");
        }

        std::regex soko_elems("[#@$*.+]+");
        std::vector<std::string> level;

        for (std::string line; std::getline(level_file, line);) {
            if (std::regex_search(line, soko_elems)) {
                level.push_back(line);
            }
            else if (!level.empty()) {
                break;
            }
        }

        if (level.size() > 2) {
            std::string path = entry.path().u8string();
            std::regex level_num_reg("(\\d+)\\.xsb$");
            std::smatch match;

            if (std::regex_search(path, match, level_num_reg)) {
                ordered_levels[std::stoi(match[1])] = level;
            }
            else {
                auto msg = "Could not parse level number from " + path;
                throw std::invalid_argument(msg);
            }
        }
    }

    for (auto &[_, level] : ordered_levels) {
        levels.push_back(level);
    }
}

extern "C" {

void sokoban_initialize() {
    read_levels();
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
    return soko.rewind();
}

bool sokoban_redo() {
    return soko.redo();
}

const char *sokoban_sequence() {
    sequence_str = soko.sequence();
    return sequence_str.c_str();
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

} // extern "C"

int main() {
}

