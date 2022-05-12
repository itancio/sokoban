#ifndef __SOKOBAN_H__
#define __SOKOBAN_H__

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

/**
 * A Sokoban game state, containing a vector of levels, a current level, and methods 
 * to operate on the level and retrieve information about its state
*/
class Sokoban {
public:
    /**
     * The four cardinal directions which represent a movement to an adjacent cell
    */
    enum Direction {
        U = 'U',
        D = 'D',
        L = 'L',
        R = 'R'
    };

private:
    /**
     * Hashing for pairs which packs the two unsigned ints into a single unique number
    */
    struct PairHash {
        size_t operator() (const std::pair<unsigned int, unsigned int> &p) const {
            return (std::hash<long>()(p.first) << 16) |
                std::hash<long>()(p.second);
        }
    };

    /**
     * Equality for pairs which checks the two members are equal
    */
    struct PairEqual {
        bool operator() (const std::pair<unsigned int, unsigned int> &left, 
            const std::pair<unsigned int, unsigned int> &right) const {
            return left.first == right.first && left.second == right.second;
        }
    };
    
    /**
     * All valid Sokoban cell symbols
    */
    enum Cell {
        PLAYER = '@',
        PLAYER_ON_GOAL = '+',
        BOX = '$',
        BOX_ON_GOAL = '*',
        GOAL = '.',
        WALL = '#',
        EMPTY = ' '
    };

    /**
     * Converts Directions to a pair of y, x delta coordinates for a movement
    */
    std::unordered_map<Direction, std::pair<int, int>> dir_offsets {
        {L, std::make_pair(0, -1)},
        {R, std::make_pair(0, 1)},
        {U, std::make_pair(-1, 0)},
        {D, std::make_pair(1, 0)}
    };

    /**
     * A vector of all of the levels this Sokoban instance was constructed with
    */
    std::vector<std::vector<std::string>> levels;

    /**
     * The current active board
    */
    std::vector<std::string> _board;

    /**
     * The current level number
    */
    unsigned int current_level;

    /**
     * The player's y and x coordinates (row, column) on _board
     */
    unsigned int py;
    unsigned int px;

    /**
     * The vector of all the moves performed on the current _board so far
    */
    std::vector<Direction> moves;

    /**
     * The history of all moves for undo/redo purposes
    */
    std::vector<std::pair<std::vector<std::string>, bool>> history;

    /**
     * A redo buffer
    */
    std::vector<std::pair<Direction, std::vector<std::string>>> undone;

    /**
     * Locates the player ('@' or '+') on the board, setting the py and px instance values
    */
    void locate_player();

    /**
     * Moves the player by dy, dx on the current board, where dy and dx are dir_offsets
     * @param int dy the directional offset on the row axis
     * @param int dx the directional offset on the column axis
    */
    void move_player(int dy, int dx);

    /**
     * Pushes a box relative to dy, dx on the current board, where dy and dx are dir_offsets
     * @param int dy the directional offset on the row axis
     * @param int dx the directional offset on the column axis
    */
    void push_box(int dy, int dx);

    /**
     * Updates metadata such as history associated with a move
     * @param Direction direction the move just made
    */
    void update(Direction direction);

    /**
     * Attempts to make a move
     * @param Direction direction the move to attempt
     * @return true if the move modified the board state, false otherwise
    */
    bool make_move(Direction direction);

public:
    /**
     * Constructor which accepts a vector of levels
    */
    Sokoban(std::vector<std::vector<std::string>> levels);

    /**
     * Return the current level number being played
     * unsigned int level the level number
    */
    unsigned int level();

    /**
     * Set the current level if possible
     * @param unsigned int level the level number to switch to
    */
    void change_level(unsigned int level_number);

    /**
     * Determine if the board is in a solved state
     * @return bool true if solved false otherwise
    */
    bool solved();

    /**
     * Getter for the current Sokoban board
     * @return std::vector<std::string> the current board
    */
    std::vector<std::string> board();

    /**
     * Moves the player one step in a Direction
     * @param Direction direction the direction to move in
     * @return true if the move modified the board state, false otherwise
    */
    bool move(Direction direction);

    /**
     * Moves the player to y, x if possible
     * @param unsigned int y the destination y-coordinate (row)
     * @param unsigned int x the destination x-coordinate (column)
     * @return true if the move modified the board state, false otherwise
    */
    bool move(unsigned int y, unsigned int x);

    /**
     * Undo the last move, if possible
     * @return bool true if the undo modified the board, false otherwise
    */
    bool undo();  

    /**
     * Redo the last undo action, if possible
     * @return bool true if the redo modified the board, false otherwise
    */
    bool redo();

    /**
     * Reset the current level to its original state
    */
    void reset();

    /**
     * Rewind the last move, if possible. This differs from undo in that 
     * a rewind considers multi-step leaps as one operation, as in move(y, x).
     * @return bool true if the undo modified the board, false otherwise
    */
    bool rewind();

    /**
     * Return the sequence of moves ("u", "d", "l", "r") 
     * applied so far on the level
     * @return std::string the moves string
    */
    std::string sequence();

    /**
     * Prints the current board state to stdout
    */
    void print_board();
};
#endif
