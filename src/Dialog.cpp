#include "Dialog.hpp"

Dialog::Dialog(int width, int height, const std::string& title = "Unnamed window")
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
}
