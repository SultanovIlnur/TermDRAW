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

const std::string DEFAULT_PROJECT_NAME = "Unnamed project";

std::string projectName;
bool running = true;

Focus currentFocus = Focus::Canvas;
Toolbar toolbar = Toolbar();

void drawUi() {
    Panel mainWindow {{1, 1}, getTerminalSize(), DOS_COLOR, 0};
    mainWindow.draw();
    toolbar.draw(currentFocus);

    moveCursor((getTerminalSize().x - 1 - DEFAULT_PROJECT_NAME.length() - 2) / 2, 1);
    std::cout << "[ TermDRAW - ";
    if (projectName.empty()) {
        std::cout << "*";
        std::cout << " " << DEFAULT_PROJECT_NAME;
    }
    std::cout << projectName << " ]";


    moveCursor(8, 9);
    std::cout << "Welcome to the TermDRAW! Easy-to-use terminal drawing tool";
    moveCursor(8, 11);
    std::cout << "Made by Ilnur Sultanov (c) 2026";
    moveCursor(8, 13);
    std::cout << "Press q key to quit the program";
}

void toggleFocus() {
    if (currentFocus == Focus::Canvas) {
        currentFocus = Focus::Toolbar;
    } else {
        currentFocus = Focus::Canvas;
    }
}

int main()
{
    init();
    while (running) {
        drawUi();
        std::cout.flush();
        SpecialKey key = readKey();
        if (key == SpecialKey::KEY_TAB) {
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

        std::cout.flush();
        if (key == SpecialKey::KEY_Q) {
            running = false;
        }
    }

    shutdown();

    return 0;
}
