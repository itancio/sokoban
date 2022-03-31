#include "sokoban.hpp"

#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <stdexcept>

Sokoban::Sokoban(std::vector<std::vector<std::string>> levels) {
    this->levels = levels;
    current_level = 0;
    _board = levels.at(current_level);
    locate_player();
    history.push_back(_board);
}

void Sokoban::print_board() {
    for (const std::string &row : board()) {
        std::cout << row << '\n';
    }
}

unsigned int Sokoban::level() {
    return current_level;
}

bool Sokoban::solved() {
    for (const std::string &row : board()) {
        for (const char cell : row) {
            if (cell == Cell::GOAL ||
                cell == Cell::PLAYER_ON_GOAL) {
                return false;
            }
        }
    }
    return true;
}

std::vector<std::string> Sokoban::board() {
    return _board;
}

void Sokoban::locate_player() {
    for (unsigned int y = 0; y < _board.size(); y++) {
        for (unsigned int x = 0; x < _board[y].size(); x++) {
            if (_board[y][x] == Cell::PLAYER ||
                _board[y][x] == Cell::PLAYER_ON_GOAL) {
                px = x;
                py = y;
                return;
            }
        }
    }
    throw std::invalid_argument("Player not found...");
}

void Sokoban::move_player(int dy, int dx) {
    // Set the cell state when player leaves the current cell
    _board[py][px] = (_board[py][px] == Cell::PLAYER_ON_GOAL) ? 
        Cell::GOAL : Cell::EMPTY;

    // Set the cell state when player arrives the new cell
    _board[py+dy][px+dx] = (_board[py+dy][px+dx] == Cell::GOAL) ? 
        Cell::PLAYER_ON_GOAL : Cell::PLAYER;
    py += dy;
    px += dx;
}

void Sokoban::push_box(int dy, int dx) {
    // Set the cell state when box leaves the current cell
    _board[py+dy][px+dx] = (_board[py+dy][px+dx] == Cell::BOX_ON_GOAL) ? 
        Cell::GOAL : Cell::EMPTY;

    // Set the cell state when box arrives the new cell
    _board[py+dy+dy][px+dx+dx] = (_board[py+dy+dy][px+dx+dx] == Cell::GOAL) ? 
        Cell::BOX_ON_GOAL : Cell::BOX;
}

/* Update move with associated board state */
void Sokoban::update(Direction direction) {
    moves.push_back(direction);
    history.push_back(_board);
}

bool Sokoban::make_move(Direction direction) {
    int dy = dir_offset[direction].y;
    int dx = dir_offset[direction].x;

    // Player moves to a goal or empty cell
    if (_board[py+dy][px+dx] == Cell::GOAL || 
        _board[py+dy][px+dx] == Cell::EMPTY) {

        move_player(dy, dx);
        update(direction);

        return true;
    }

    // Player encounters a box or box on goal
    if (_board[py+dy][px+dx] == Cell::BOX ||
        _board[py+dy][px+dx] == Cell::BOX_ON_GOAL) {
        
        // If the cell next to the box is a goal or empty cell,
        // then the player can push box to that cell
        if (_board[py+dy+dy][px+dx+dx] == Cell::EMPTY ||
            _board[py+dy+dy][px+dx+dx] == Cell::GOAL) {

            push_box(dy, dx);
            move_player(dy, dx);
            update(direction);

            return true;
        }
    }

    return false;
}

bool Sokoban::move(Direction direction) {
    undone.clear();

    return make_move(direction);
}

bool Sokoban::move(unsigned int y, unsigned int x) {

    // If the specified destination is the same, don't do anything
    if (py == y && px == x) {
        return false;
    }

    std::queue<Node> queue;
    std::unordered_map<Node, Node, KeyHash, KeyEqual> visited;
 
    bool destination_found = (py == y && px == x);

    // Add origin to the queue and visited map
    Node origin(py, px);
    Node destination(y, x);
    queue.push(origin);
    visited[origin] = Node(0, 0);

    // Visit all paths to a destination if possible
    while (!queue.empty()) {
        // Get the first node from the queue
        Node current = queue.front();
        queue.pop();

        //std::cout << "current: " << current.y << " " << current.x << std::endl;

        // Get neighbors
        std::vector<Node> neighbors;
        for (const auto &[key, value] : dir_offset) {

            // Check the cardinal adjacent neighbors if they are a valid path.
            // A valid path is a path that has not yet been visited, and
            // a goal or empty cell.
            Node adj = Node(current.y + value.y, current.x + value.x);
            // std::cout << "adj: " << adj.y << " " << adj.x << " " << (visited.find(adj) != visited.end()) << " ";
            if ((visited.find(adj) == visited.end()) &&
                (_board.at(adj.y).at(adj.x) == Cell::EMPTY || 
                _board.at(adj.y).at(adj.x) == Cell::GOAL)) {
                neighbors.push_back(adj);
            }
        }
        //std::cout << std::endl;

        // Add neighbors to visited with its associated parent, and then queue
        for (auto &neighbor : neighbors) {
            visited[neighbor] = current;
            queue.push(neighbor);
        }
    
        // Exit the loop once we are currently in the destination
        if (current == destination) {
            destination_found = true;
            break;
        }
    }
    
    if (!destination_found) {
        return false;
    }
    
    // print visited
    // for (auto &[key, value] : visited) {
    //     std::cout << "(" << key.y << ", " << key.x << ") : [" << value.y << ", " << value.x << "]" << std::endl;
    // }

    // Needed for comparing nodes
    std::unordered_map<Node, Node, KeyHash, KeyEqual>::hasher hasher = visited.hash_function();

    // Build the valid path from the origin to the destination
    std::stack<Node> paths;
    Node current = destination;

    while (hasher(origin) != hasher(current)) {
        paths.push(current);
        std::cout << "(" << paths.top().y << ", " << paths.top().x << ")" << std::endl;
        std::cout << hasher(origin) << " : (" << origin.y << ", " << origin.x << ")" << "   ";
        std::cout << hasher(current) << " : (" << current.y << ", " << current.x << ")" << std::endl;
        
        current = visited[current];
        
        std::cout << "condition: " << (current != origin) << std::endl;
        std::cout << hasher(current) << " : (" << current.y << ", " << current.x << ")" << std::endl;
    }

    // print paths
    std::stack<Node> temp;
    while (!paths.empty()) {
        temp.push(paths.top());
        paths.pop();
    }
    while (!temp.empty()) {
        Node n = temp.top();
        std::cout << "paths : (" << n.y << ", " << n.x << ")" << "  ";
        paths.push(temp.top());
        temp.pop();
    }

    
    // Execute move for every path in paths
    current = origin;

    while (!paths.empty()) {
        Node next = paths.top();
        Node offset = Node(next.y - current.y, next.x - current.x);

        std::cout << "next : (" << next.y << ", " << next.x << ")" << "  " << std::endl;
        std::cout << "diff : (" << next.y - current.y << ", " << next.x - current.x << ")" << "  " << std::endl;
        std::cout << "offset : (" << offset.y << ", " << offset.x << ")" << std::endl;

        // TODO: Edit
        for (auto &direction : {Direction::U, Direction::D, Direction::L, Direction::R}) {
            if (offset == dir_offset.at(direction)) {
                move(direction);
            }
        }
        

        current = next;
        paths.pop();
        print_board();
    }

    return true;
}


bool Sokoban::undo() {
    if (moves.empty()) {
        return false;
    }

    undone.push_back(std::make_pair(moves.back(), _board));

    moves.pop_back();
    history.pop_back();

    _board = history.back();
    locate_player();

    return true;
}

bool Sokoban::redo() {
    if (undone.empty()) {
        return false;
    }

    Direction direction = undone.back().first;
    _board = undone.back().second;
    update(direction);

    undone.pop_back();

    locate_player();

    return true;
}