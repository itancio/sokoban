#include <iostream>

#include "counter.hpp"

//#include <emscripten/emscripten.h>

/* this file is the interface for JS */

Counter c;

extern "C" {
int click(int num, char *s) {
    // pass some random args from JS just to show that it can be done
    std::cout << "click called with args (" << num << ", " << s << ")\n";
    c.increment();
    return c.count;
}
}

//int main() {
//    std::cout << "Hello Emscripten!\n";
//}
