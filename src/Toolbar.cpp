#include "Toolbar.hpp"

Toolbar::Toolbar() : activeMenu(false), selectedButton(0) {
    initMenu();
}

int calculateDistance(const std::string& text) {
    return text.length() + 3;
}

void Toolbar::draw(Focus currentFocus) {
    bool isFocused = currentFocus == Focus::Toolbar;
    
    unsigned short int currentDistance = 2;
    unsigned short int i = 0;
    for (const auto& menu : menus) {
        moveCursor(currentDistance, 2);
        if (isFocused && selectedButton == i) {
            std::cout << "\033[7m"; // inverse color
        }
            std::cout << "[" << menu.caption << "]";
            currentDistance += calculateDistance(menu.caption);
            std::cout << "\033[27m"; // reset color
            std::cout << " ";
        i++;
    }
    moveCursor(3, getTerminalSize().y - 1);
    std::cout << "Current mode: " << getCurrentMode(currentFocus);
}

void Toolbar::initMenu() {
    MenuSection fileMenu;
    fileMenu.caption = "File";
    fileMenu.items.push_back({"New file", nullptr});
    fileMenu.items.push_back({"Open file", nullptr});
    fileMenu.items.push_back({"Save file", nullptr});
    fileMenu.items.push_back({"Exit", nullptr});

    MenuSection editMenu;
    editMenu.caption = "Edit";
    // TODO ADD ITEMS

    MenuSection optionMenu;
    optionMenu.caption = "Options";
    // TODO ADD ITEMS

    MenuSection helpMenu;
    helpMenu.caption = "Help";
    helpMenu.items.push_back({"About", nullptr});
    helpMenu.items.push_back({"Settings", nullptr});

    menus.push_back(fileMenu);
    menus.push_back(editMenu);
    menus.push_back(optionMenu);
    menus.push_back(helpMenu);
}

bool Toolbar::handleInput(int key) {
    // TODO

    return false;
}