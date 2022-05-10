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

/**
 * Reads all levels from a directory into the levels vector
 * @param path the path to the directory
*/
void read_levels(const std::string path = "src/engine/levels") {
    std::map<int, std::vector<std::string>> ordered_levels;
    std::filesystem::path levels_dir =
        std::filesystem::directory_entry(path);

    for (const auto& entry : std::filesystem::directory_iterator(levels_dir)) {
        std::ifstream level_file(entry.path());
        const std::string path = entry.path().u8string();

        if (!level_file) {
            throw std::invalid_argument("Cannot open file " + path);
        }

        const std::regex soko_elems_reg("[#@$*.+ ]+");
        std::vector<std::string> level;

        for (std::string line; std::getline(level_file, line);) {
            if (std::regex_match(line, soko_elems_reg)) {
                level.push_back(line);
            }
            else if (!level.empty()) {
                break;
            }
        }

        if (level.size() > 2) {
            const std::regex level_num_reg("(\\d+)\\.xsb$");
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

// Glue code to be called by the JS UI
// to interact with the game engine
extern "C" {

/**
 * Initializes the Sokoban game by reading the levels
*/
void sokoban_initialize() {
    read_levels();
    std::vector<std::string> test_level = {
        "#####  ###",
        "#.  ####.#",
        "#$       #",
        "#   ##   #",
        "##      ##",
        " #  *   #",
        "##      ##",
        "# @  $$$ #",
        "#        #",
        "#.#### . #",
        "###  #####",
    };
    levels.push_back(test_level);
    soko = {levels};
}

/**
 * Stringifies the current Sokoban board
 * @return const char * the board delimited by newlines
*/
const char *sokoban_board_to_string() {
    auto board = soko.board();
    joined_board = std::accumulate(
        std::begin(board), std::end(board), std::string(),
        [](std::string &ss, std::string &s)
        { return ss.empty() ? s : ss + "\n" + s; }
    );
    return joined_board.c_str();
}

/**
 * Moves the player in a direction relative to their current location
 * @param char *s "u", "d", "l", "r" corresponding to the 4 directions
 * @return bool true if the move modified the board, false otherwise
*/
bool sokoban_move(char *s) {
    return soko.move((Sokoban::Direction) *s);
}

/**
 * Moves the player to row, col if possible
 * @param int row the row to move to
 * @param int col the column to move to
 * @return bool true if the move modified the board, false otherwise
*/
bool sokoban_goto(int row, int col) {
    return soko.move(row, col);
}

/**
 * Determine if the board is in a solved state
 * @return bool true if solved false otherwise
*/
bool sokoban_solved() {
    return soko.solved();
}

/**
 * Undo the last move, if possible
 * @return bool true if the undo modified the board, false otherwise
*/
bool sokoban_undo() {
    return soko.rewind();
}

/**
 * Reset the current level to its original state
*/
void sokoban_reset() {
    soko.reset();
}

/**
 * Return the sequence of moves ("u", "d", "l", "r") 
 * applied so far on the level
 * @return const char * the moves string
*/
const char *sokoban_sequence() {
    sequence_str = soko.sequence();
    return sequence_str.c_str();
}

/**
 * Return the current level number being played
 * int level the level number
*/
int sokoban_level() {
    return soko.level();
}

/**
 * Set the current level if possible
 * @param int level the level number to switch to
*/
void sokoban_change_level(int level) {
    soko.change_level(level);
}

/**
 * Return the number of levels in the levels vector
 * @return int the size of the levels vector
*/
int sokoban_levels_size() {
    return levels.size();
}

} // extern "C"

int main() {
}

