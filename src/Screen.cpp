#include "Screen.hpp"

void moveCursor(int x, int y) {
    std::cout << "\033[" << y << ";" << x << "H";
}

Position2D getTerminalSize() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return {w.ws_col, w.ws_row};
}