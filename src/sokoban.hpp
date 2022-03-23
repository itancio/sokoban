#ifndef __SOKOBAN_H__
#define __SOKOBAN_H__

#include <string>
#include <unordered_map>
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
    enum Cell {
        PLAYER = '@',
        PLAYER_ON_GOAL = '+',
        BOX = '$',
        BOX_ON_GOAL = '*',
        GOAL = '.',
        WALL = '#',
        EMPTY = ' '
    };

    std::unordered_map<Direction, std::vector<int>> dir_offset {
        {Direction::U, {-1, 0}},
        {Direction::D, {1, 0}},
        {Direction::L, {0, -1}},
        {Direction::R, {0, 1}}
    };

    std::unordered_map<Direction, Direction> opposite {
        {Direction::U, Direction::D},
        {Direction::D, Direction::U},
        {Direction::R, Direction::L},
        {Direction::L, Direction::R},
    };

    std::vector<std::vector<std::string>> levels;
    std::vector<std::string> _board;
    unsigned int current_level;
    unsigned int py;
    unsigned int px;
    std::vector<Direction> moves;
    std::vector<Direction> undone;

    void locate_player();
    void move_player(int dy, int dx);
    void push_box(int dy, int dx);
    void pull_box(int dy, int dx);
    bool make_move(Direction direction);

public:
    Sokoban(std::vector<std::vector<std::string>> levels);
    unsigned int level();
    bool solved();
    std::vector<std::string> board();
    bool move(Direction direction);
    bool undo();  
    bool redo();
    
    void print_board();  
};

#endif