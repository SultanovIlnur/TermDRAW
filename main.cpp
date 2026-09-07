#include <iostream>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <memory>

#include "src/Focus.hpp"
#include "src/MenuItem.hpp"
#include "src/Panel.hpp"
#include "src/Screen.hpp"
#include "src/Toolbar.hpp"
#include "src/ToolbarButton.hpp"
#include "src/Canvas.hpp"
#include "src/Dialog.hpp"
#include "src/Toolbox.hpp"

// Ilnur Sultanov (C) 2026

// 02 Sept 2026: This is only a boilerplate code that I'm planning to rework later

const std::string DEFAULT_PROJECT_NAME = "Unnamed project";

Canvas canvas;
std::string projectName;
Toolbox toolbox;

Focus currentFocus = Focus::Dialog;
Toolbar toolbar = Toolbar(canvas);
std::unique_ptr<Dialog> activeDialog;

bool running = true;

void drawUi() {
    Panel mainWindow {{1, 1}, getTerminalSize(), DOS_COLOR, 0};
    mainWindow.draw();

    moveCursor((getTerminalSize().x - 1 - DEFAULT_PROJECT_NAME.length() - 2) / 2, 1);
    std::cout << "[ TermDRAW - ";
    if (projectName.empty()) {
        std::cout << "*";
        std::cout << " " << DEFAULT_PROJECT_NAME;
    }
    std::cout << projectName << " ]";

    canvas.draw();
    toolbox.draw(currentFocus == Focus::Toolbox);
    toolbar.draw(currentFocus);
    if (activeDialog) {
        activeDialog->draw();
    }
}

void toggleFocus() {
    if (currentFocus == Focus::Canvas) {
        currentFocus = Focus::Toolbar;
    } else if (currentFocus == Focus::Toolbar) {
        currentFocus = Focus::Toolbox;
    } else {
        currentFocus = Focus::Canvas;
    }
}

void initWelcomeDialog() {
    activeDialog = std::make_unique<Dialog>(62, 14, "Welcome to TermDRAW");

    activeDialog->addLine(R"(   ______                    ____  ____  ___ _       __  )");
    activeDialog->addLine(R"(  /_  __/__  _________ ___  / __ \/ __ \/   | |     / /  )");
    activeDialog->addLine(R"(   / / / _ \/ ___/ __ `__ \/ / / / /_/ / /| | | /| / /   )");
    activeDialog->addLine(R"(  / / /  __/ /  / / / / / / /_/ / _, _/ ___ | |/ |/ /    )");
    activeDialog->addLine(R"( /_/  \___/_/  /_/ /_/ /_/_____/_/ |_/_/  |_|__/|__/     )");
    activeDialog->addLine("");
    activeDialog->addLine("Welcome to TermDRAW! Easy-to-use terminal drawing tool");
    activeDialog->addLine("Ilnur Sultanov (c) 2026");

    activeDialog->addButton("Close", nullptr);
    activeDialog->addButton("GitHub", []() {
        system("xdg-open https://github.com/SultanovIlnur/TermDRAW > /dev/null 2>&1 &");
    });
}

int main()
{
    init();
    initWelcomeDialog();
    while (running) {
        drawUi();
        std::cout.flush();
        SpecialKey key = readKey();

        if (currentFocus == Focus::Dialog && activeDialog) {
            activeDialog->handleInput(key);
            if (activeDialog->shouldClose()) {
                activeDialog.reset();
                currentFocus = Focus::Canvas;
            }
        }
        else if (key == SpecialKey::KEY_TAB) {
            toggleFocus();
        }
        else {
            switch (currentFocus) {
                case Focus::Toolbar:
                    toolbar.handleInput(key);
                    break;
                case Focus::Canvas:
                    canvas.handleInput(key);
                    break;
                case Focus::Toolbox:
                    toolbox.handleInput(key);
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
