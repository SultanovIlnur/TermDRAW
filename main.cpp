#include <iostream>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "main.hpp"

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

struct Layer {
    int value;
    bool visibility;
};

struct Position2D {
    int x;
    int y;
};

class Panel {
    public:
        Panel(Position2D start, Position2D end, std::string color, int layerValue)
        : startPos(start), endPos(end), color(color), layer{ layerValue, true} {}

        void draw() {
            moveCursor(startPos.x, startPos.y);
            std::cout << "+";

            for (int x = startPos.x + 1; x < endPos.x; x++)
                std::cout << "-";

            std::cout << "+";

            for (int y = startPos.y + 1; y < endPos.y; y++)
            {
                moveCursor(startPos.x, y);
                std::cout << "|";

                for (int x = startPos.x + 1; x < endPos.x; x++)
                    std::cout << " ";

                std::cout << "|";
            }

            moveCursor(startPos.x, endPos.y);
            std::cout << "+";

            for (int x = startPos.x + 1; x < endPos.x; x++)
                std::cout << "-";

            std::cout << "+";
        }

    private:
        Layer layer;
        Position2D startPos;
        Position2D endPos;
        std::string color;
};

struct ToolbarButton {
    Layer layer;
    std::string caption;


};

struct Toolbar {
};

void moveCursor(int x, int y)
{
    std::cout << "\033[" << y << ";" << x << "H";
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

        char c = cin.get();
        if (c == 'q') {
            running = false;
        }
    }

    shutdown();

    return 0;
}
