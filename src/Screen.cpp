#include "Screen.hpp"
#include <iostream>

void moveCursor(int x, int y) {
    std::cout << "\033[" << y << ";" << x << "H";
}