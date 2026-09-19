#include "Toolbar.hpp"

Toolbar::Toolbar(Canvas& canvas) : canvas(canvas), activeMenu(false), activeSubMenu(false), selectedButton(0), selectedSubMenuButton(0) {
    initMenu();
}

int calculateDistance(const std::string& text) {
    return text.length() + 3;
}

void Toolbar::draw(Focus currentFocus) {
    bool isFocused = currentFocus == Focus::Toolbar;
    
    int currentDistance = 2;
    int i = 0;
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
    Position2D term = getTerminalSize();

    moveCursor(1, term.y - 2);
    std::cout << "╠";
    for (int x = 2; x < term.x; ++x) {
        std::cout << "═";
    }
    std::cout << "╣";

    moveCursor(2, term.y - 1);
    for (int x = 2; x < term.x; ++x) {
        std::cout << " ";
    }

    moveCursor(3, term.y - 1);
    Position2D cur = canvas.getCursor();
    if (canvas.getIsDrawing()) {
        std::cout << "\033[7m Enter \033[27m Place  ";
        std::cout << "\033[7m Esc \033[27m Cancel";
    } else {
        std::cout << "\033[7m Tab \033[27m Focus  ";
        std::cout << "\033[7m Enter \033[27m Draw  ";
        std::cout << "\033[7m C \033[27m Color  ";
        std::cout << "\033[7m Q \033[27m Quit";
    }
    std::cout << " │ Mode: " << getCurrentMode(currentFocus);
    std::cout << " │ " << cur.x << "," << cur.y;
    std::cout << " │ " << canvas.getCurrentColor() << "■ " << canvas.getCurrentColorName() << DOS_COLOR;

    if (activeSubMenu) {
        const auto& currentSection = menus[selectedButton];
        
        int menuWidth = 16;
        for (const auto& item : currentSection.items) {
            if (static_cast<int>(item.caption.length()) + 4 > menuWidth) {
                menuWidth = static_cast<int>(item.caption.length()) + 4;
            }
        }
        int menuHeight = static_cast<int>(currentSection.items.size()) + 1;
        
        Panel popupPanel(
            {selectedX, 3}, 
            {selectedX + menuWidth, 3 + menuHeight}, 
            "\033[93;44m", 
            1
        );
        popupPanel.draw();
        for (const auto& item : currentSection.items) {
            if (selectedSubMenuButton == &item - &currentSection.items[0]) {
                std::cout << "\033[7m";
            }
            moveCursor(selectedX + 1, 4 + &item - &currentSection.items[0]);
            std::cout << item.caption;
            std::cout << "\033[27m";
        }
    }
}

void Toolbar::initMenu() {
    MenuSection fileMenu;
    fileMenu.caption = "File";
    fileMenu.items.push_back({"New file", [this]() { canvas.clear(); }});
    fileMenu.items.push_back({"Open file", [this]() { canvas.loadFromFile("drawing.td"); }});
    fileMenu.items.push_back({"Save file", [this]() { canvas.saveToFile("drawing.td"); }});
    fileMenu.items.push_back({"Export PNG", [this]() { canvas.exportImage("drawing.png", "png"); }});
    fileMenu.items.push_back({"Export BMP", [this]() { canvas.exportImage("drawing.bmp", "bmp"); }});
    fileMenu.items.push_back({"Export JPG", [this]() { canvas.exportImage("drawing.jpg", "jpg"); }});
    fileMenu.items.push_back({"Exit", actionShutdown});

    MenuSection editMenu;
    editMenu.caption = "Edit";

    MenuSection optionMenu;
    optionMenu.caption = "Options";
    for (size_t i = 0; i < PALETTE.size(); ++i) {
        optionMenu.items.push_back({PALETTE[i].name, [this, i]() { canvas.setColorIndex(static_cast<int>(i)); }});
    }

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
            if (!activeSubMenu) {
                activeSubMenu = true;
                selectedSubMenuButton = 0;
            } else {
                const auto& currentSection = menus[selectedButton];
                if (selectedSubMenuButton < currentSection.items.size()) {
                    auto action = currentSection.items[selectedSubMenuButton].action;
                    if (action) {
                        action();
                    }
                }
                activeSubMenu = false;
            }
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
        case SpecialKey::ARROW_KEY_DOWN:
            if (activeSubMenu) {
                if (selectedSubMenuButton < menus[selectedButton].items.size() - 1) {
                    selectedSubMenuButton++;
                }
            }
            break;
        
        case SpecialKey::ARROW_KEY_UP:
            if (activeSubMenu) {
                if (selectedSubMenuButton > 0) {
                    selectedSubMenuButton--;
                }
            }
            break;
        case SpecialKey::KEY_ESC:
            if (activeSubMenu) {
                activeSubMenu = false;
                selectedSubMenuButton = 0;
            } else {
                activeMenu = false;
            }
    }
    return true;
}