#include <iostream>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "src/Focus.hpp"
#include "src/MenuItem.hpp"
#include "src/Panel.hpp"
#include "src/Screen.hpp"
#include "src/Toolbar.hpp"
#include "src/ToolbarButton.hpp"

// Ilnur Sultanov (C) 2026

// 02 Sept 2026: This is only a boilerplate code that I'm planning to rework later

const std::string CLEAR_SCREEN = "\033[2J";
const std::string RESET        = "\033[0m";
const std::string MOVE_HOME    = "\033[H";
const std::string HIDE_CURSOR  = "\033[?25l";
const std::string SHOW_CURSOR  = "\033[?25h";

const std::string DOS_COLOR = "\033[93;44m";

const std::string DEFAULT_PROJECT_NAME = "Unnamed project";

std::string projectName;
bool running = true;
struct termios originalTermios;

Focus currentFocus = Focus::Canvas;

void initMenu() {
}

void init()
{
    initMenu();
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

Position2D getTerminalSize() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return {w.ws_col, w.ws_row};
}

void drawUi() {
    // Main DOS window
    Panel mainWindow {{1, 1}, getTerminalSize(), DOS_COLOR, 0};
    mainWindow.draw();

    moveCursor((getTerminalSize().x - 1 - DEFAULT_PROJECT_NAME.length() - 2) / 2, 1);
    std::cout << "[ TermDRAW - ";
    if (projectName.empty()) {
        std::cout << "*";
        std::cout << " " << DEFAULT_PROJECT_NAME;
    }
    std::cout << projectName << " ]";
}

int main()
{
    init();

    while (running) {
        int key = std::cin.get();
        if (key == KEY_F10 || key == KEY_TAB) {
            toggleFocus();
        } else {
            switch (currentFocus) {
                case Focus::Toolbar:
                    if (!toolbar.handleInput(key)) {
                    }
                    break;
                case Focus::MenuPopup:
                    break;
                case Focus::Canvas:
                    break;
                
                default:
                    break;
            }
        }
        drawUi();

        moveCursor(8, 9);
        std::cout << "Welcome to the TermDRAW! Easy-to-use terminal drawing tool";
        moveCursor(8, 12);
        std::cout << "Made by Ilnur Sultanov (c) 2026";
        moveCursor(8, 15);
        std::cout << "Press q key to quit the program";

        std::cout.flush();

        char c = std::cin.get();
        if (c == 'q') {
            running = false;
        }
    }

    shutdown();

    return 0;
}
