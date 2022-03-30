#ifndef __NODE_CPP__
#define __NODE_CPP__

#include <utility>

struct Node {
    
    unsigned int y;
    unsigned int x;

    Node() {}
    Node(unsigned int y, unsigned int x) {
        this->y = y;
        this->x = x;
    }

    bool operator==(const Node& p) {
        return (x == p.x && y == p.y);
    }

    bool operator!=(const Node& p) {
        return (x != p.x && y != p.y);
    }

};

struct KeyHash {
    size_t operator() (const Node& p) const {
        return std::hash<int>()(p.y) ^
            (std::hash<int>()(p.x) << 1);
    }
};

struct KeyEqual {
    bool operator() (const Node& left, const Node& right) const {
        return left.y == right.y && left.x == right.x;
    }
};


#endif