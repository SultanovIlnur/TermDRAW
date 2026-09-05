#include <iostream>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

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

std::vector<MenuSection> menus;
int activeMenu = -1;

void initMenu() {
    MenuSection fileMenu;
    fileMenu.title = "File";
    fileMenu.items.push_back({"New file", nullptr});
    fileMenu.items.push_back({"Open file", nullptr});
    fileMenu.items.push_back({"Save file", nullptr});
    fileMenu.items.push_back({"Exit", nullptr});

    MenuSection editMenu;
    editMenu.title = "Edit";
    // TODO ADD ITEMS

    MenuSection optionMenu;
    optionMenu.title = "Option";
    // TODO ADD ITEMS

    MenuSection helpMenu;
    helpMenu.title = "Help";
    helpMenu.items.push_back({"About", nullptr});
    helpMenu.items.push_back({"Settings", nullptr});

    menus.push_back(fileMenu);
    menus.push_back(editMenu);
    menus.push_back(optionMenu);
    menus.push_back(helpMenu);
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

int getCaptionDistance(std::string inputText) {
    return inputText.length() + 2;
}

void drawToolbarButton(std::string buttonText) {

}

void getToolbarOptions() {

}

void drawSubToolbar() {
    // we need to use layers to draw subtoolbar in front of the regular toolbar imo
}

void drawToolbar() {
    // firstly we need to draw toolbar button and then put them in an array
    int currentBtn = 0;

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

    // draw toolbar
    drawToolbar();

    // moveCursor(8, 4);
    // std::cout << "File";

    // moveCursor(15, 4);
    // std::cout << "Edit";

    // moveCursor(22, 4);
    // std::cout << "Options";

    // moveCursor(32, 4);
    // std::cout << "Help";
}

int main()
{
    init();

    while (running) {
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
