#ifndef __SOKOBAN_H__
#define __SOKOBAN_H__

#include <string>
#include <vector>

class Sokoban {
    std::vector<std::vector<std::string>> levels;
    unsigned int current_level;
    std::vector<std::string> _board;
public:
    Sokoban(std::vector<std::vector<std::string>> levels);
    unsigned int level();
    std::vector<std::string> board();
};

#endif
