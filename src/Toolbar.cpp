#include "Toolbar.hpp"

Toolbar::Toolbar() : activeMenu(-1) {}

void Toolbar::draw() {
    for (const auto& menu : menus) {
        moveCursor(1, 1);
        std::cout << "[" << menu.caption << "] ";
    }
    std::cout << std::endl;
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