#include "Screen.hpp"

struct termios originalTermios;

void moveCursor(int x, int y) {
    std::cout << "\033[" << y << ";" << x << "H";
}

Position2D getTerminalSize() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return {w.ws_col, w.ws_row};
}

void init()
{
    tcgetattr(STDIN_FILENO, &originalTermios);
    struct termios raw = originalTermios;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
    // settings dos colors
    std::cout << DOS_COLOR;
    std::cout << CLEAR_SCREEN;
    std::cout << MOVE_HOME;
    std::cout << HIDE_CURSOR;
}

void shutdown()
{
    tcsetattr(STDIN_FILENO, TCSANOW, &originalTermios);
    std::cout << RESET;
    std::cout << SHOW_CURSOR;
    std::cout << CLEAR_SCREEN;
    std::cout << MOVE_HOME;
}