#ifndef __NODE_CPP__
#define __NODE_CPP__

#include <utility>

struct Node {
    
    int y;
    int x;

    Node() {}
    Node(int y, int x) {
        this->y = y;
        this->x = x;
    }

    bool operator==(const Node &p) {
        return (x == p.x && y == p.y);
    }

    bool operator!=(const Node &p) {
        return !(x == p.x && y == p.y);
    }
};

struct KeyHash {
    size_t operator() (const Node &p) const {
        return (std::hash<long long>()(p.y) << 16) |
            std::hash<long long>()(p.x);
    }
};

struct KeyEqual {
    bool operator() (const Node &left, const Node &right) const {
        return left.y == right.y && left.x == right.x;
    }
};

#endif