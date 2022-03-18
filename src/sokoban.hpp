#ifndef __SOKOBAN_H__
#define __SOKOBAN_H__

#include <string>
#include <vector>

class Sokoban {
    std::vector<std::vector<std::string>> levels;
    std::vector<std::string> _board;
    unsigned int current_level;
    unsigned int py;
    unsigned int px;
    void locate_player();
    bool make_move(int dy, int dx);

public:
    Sokoban(std::vector<std::vector<std::string>> levels);
    unsigned int level();
    bool solved();
    std::vector<std::string> board();
    bool move(char direction);  
    void print_board();  
};

#endif
