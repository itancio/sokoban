#ifndef __SOKOBAN_H__
#define __SOKOBAN_H__

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class Sokoban {
public:
    enum Direction {
        U = 'U',
        D = 'D',
        L = 'L',
        R = 'R'
    };

private:
    struct PairHash {
        size_t operator() (const std::pair<unsigned int, unsigned int> &p) const {
            return (std::hash<long>()(p.first) << 16) |
                std::hash<long>()(p.second);
        }
    };

    struct PairEqual {
        bool operator() (const std::pair<unsigned int, unsigned int> &left, 
            const std::pair<unsigned int, unsigned int> &right) const {
            return left.first == right.first && left.second == right.second;
        }
    };
    
    enum Cell {
        PLAYER = '@',
        PLAYER_ON_GOAL = '+',
        BOX = '$',
        BOX_ON_GOAL = '*',
        GOAL = '.',
        WALL = '#',
        EMPTY = ' '
    };

    std::unordered_map<Direction, std::pair<int, int>> dir_offsets {
        {L, std::make_pair(0, -1)},
        {R, std::make_pair(0, 1)},
        {U, std::make_pair(-1, 0)},
        {D, std::make_pair(1, 0)}
    };

    std::vector<std::vector<std::string>> levels;
    std::vector<std::string> _board;
    unsigned int current_level;
    unsigned int py;
    unsigned int px;
    std::vector<Direction> moves;
    std::vector<std::vector<std::string>> history;
    std::vector<std::pair<Direction, std::vector<std::string>>> undone;

    void locate_player();
    void move_player(int dy, int dx);
    void push_box(int dy, int dx);
    void update(Direction direction);
    bool make_move(Direction direction);

public:
    Sokoban(std::vector<std::vector<std::string>> levels);
    unsigned int level();
    void change_level(unsigned int level_number);
    bool solved();
    std::vector<std::string> board();
    bool move(Direction direction);
    bool move(unsigned int y, unsigned int x);
    bool undo();  
    bool redo();
    void reset();

    void print_board();  
};
#endif
