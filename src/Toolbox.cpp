#include "Toolbox.hpp"

Toolbox::Toolbox() : selectedIndex(0) {
    tools.push_back({Tool::Rectangle, "[ □ ]"});
    tools.push_back({Tool::Line,      "[ ╱ ]"});
    tools.push_back({Tool::Circle,    "[ ○ ]"});
}

Tool Toolbox::getSelectedTool() const {
    return tools[selectedIndex].tool;
}

void Toolbox::draw(bool isFocused) const {
    Panel panel({2, 3}, {8, 7}, DOS_COLOR, 1);
    panel.draw();
    for (size_t i = 0; i < tools.size(); ++i) {
        moveCursor(3, 4 + static_cast<int>(i));
        // Если инструмент выбран — подсвечиваем инверсией
        if (static_cast<int>(i) == selectedIndex) {
            std::cout << "\033[7m";
        }
        std::cout << tools[i].icon;
        std::cout << "\033[27m";
    }
}

bool Toolbox::handleInput(SpecialKey key) {
    switch (key) {
        case SpecialKey::ARROW_KEY_UP:
            if (selectedIndex > 0) {
                selectedIndex--;
                return true;
            }
            break;
        case SpecialKey::ARROW_KEY_DOWN:
            if (selectedIndex + 1 < static_cast<int>(tools.size())) {
                selectedIndex++;
                return true;
            }
            break;
        default:
            break;
    }
    return false;
}