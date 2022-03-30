#ifndef __SOKOBAN_H__
#define __SOKOBAN_H__

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "node.cpp"

class Sokoban {
public:
    enum Direction {
            U = 'U',
            D = 'D',
            L = 'L',
            R = 'R',
            O = 'O'
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

    std::unordered_map<Direction, Node> dir_offset {
        {U, Node(-1, 0)},
        {D, Node(1, 0)},
        {L, Node(0, -1)},
        {R, Node(0, 1)}
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
    bool solved();
    std::vector<std::string> board();
    bool move(Direction direction);
    bool move(unsigned int y, unsigned int x);
    bool undo();  
    bool redo();
    
    void print_board();  
};

#endif