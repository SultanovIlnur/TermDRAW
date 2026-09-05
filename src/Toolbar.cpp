#include "Toolbar.hpp"

Toolbar::Toolbar() : activeMenu(false), activeSubMenu(false), selectedButton(0), selectedSubMenuButton(0) {
    initMenu();
}

int calculateDistance(const std::string& text) {
    return text.length() + 3;
}

void Toolbar::draw(Focus currentFocus) {
    bool isFocused = currentFocus == Focus::Toolbar;
    
    unsigned short int currentDistance = 2;
    unsigned short int i = 0;
    int selectedX = 2;
    for (const auto& menu : menus) {
        if (selectedButton == i) {
            selectedX = currentDistance;
        }

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

    if (activeSubMenu) {
        const auto& currentSection = menus[selectedButton];
        
        int menuWidth = 16;
        int menuHeight = static_cast<int>(currentSection.items.size()) + 1;
        
        Panel popupPanel(
            {selectedX, 3}, 
            {selectedX + menuWidth, 3 + menuHeight}, 
            "\033[93;44m", 
            1
        );
        popupPanel.draw();
    }
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

bool Toolbar::handleInput(SpecialKey key) {
    switch (key) {
        case SpecialKey::KEY_ENTER:
            activeSubMenu = !activeSubMenu;
            break;
        case SpecialKey::ARROW_KEY_RIGHT:
            if (selectedButton < menus.size() - 1) {
                selectedButton++;
            }
            break;
        case SpecialKey::ARROW_KEY_LEFT:
            if (selectedButton > 0) {
                selectedButton--;
            }
            break;
    }
    return true;
}