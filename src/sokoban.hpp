#ifndef __SOKOBAN_H__
#define __SOKOBAN_H__

#include <vector>
#include <string>

// class Sokoban {
//     const std::vector<std::vector<std::string>> levels;
//     int count;
    

//     Sokoban();
//     void increment();
// };

class Sokoban {

private:
    std::vector<std::vector<std::string>> levels;
    unsigned int current_level;
    std::vector<std::string> _board;
public:
    Sokoban(std::vector<std::vector<std::string>> levels);
    unsigned int level();
    std::vector<std::string> board();
};

#endif
