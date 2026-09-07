#include "Dialog.hpp"

Dialog::Dialog(int width, int height, const std::string& title)
    : width(width), height(height), title(title), selectedButton(0), needClose(false) {}

void Dialog::addLine(const std::string& line) {
    lines.push_back(line);
}

void Dialog::addButton(const std::string& caption, std::function<void()> action) {
    buttons.push_back({caption, action});
}

bool Dialog::shouldClose() const {
    return needClose;
}

void Dialog::draw() const {
    Position2D term = getTerminalSize();
    int startX = (term.x - width) / 2;
    int startY = (term.y - height) / 2;

    Panel panel({startX, startY}, {startX + width, startY + height}, DOS_COLOR, 2);
    panel.draw();

    moveCursor(startX + 2, startY);
    std::cout << "[ " << title << " ]";

    for (int i = 0; i < lines.size(); i++) {
        moveCursor(startX + 3, startY + 2 + i);
        std::cout << lines[i];
    }

    int btnY = startY + height - 2;
    int btnX = startX + 4;

    for (int i = 0; i < buttons.size(); i++) {
        moveCursor(btnX, btnY);

        if (i == selectedButton) {
            std::cout << "\033[7m[ " << buttons[i].caption << " ]\033[27m";
        } else {
            std::cout << "[ " << buttons[i].caption << " ]";
        }
        btnX += buttons[i].caption.length() + 6;
    }
}

bool Dialog::handleInput(SpecialKey key) {
    switch (key) {
        case SpecialKey::ARROW_KEY_RIGHT:
            if (selectedButton < buttons.size() - 1) selectedButton++;
            return true;
        case SpecialKey::ARROW_KEY_LEFT:
            if (selectedButton > 0) selectedButton--;
            return true;
        case SpecialKey::KEY_ENTER:
            if (buttons[selectedButton].action) {
                buttons[selectedButton].action();
            }
            needClose = true; // close the dialog
            return true;
        case SpecialKey::KEY_ESC:
            needClose = true;
            return true;
        default:
            return false;
    }
}
