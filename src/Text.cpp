#include "Text.hpp"
#include <iostream>

Text::Text(Position2D pos, const std::string& text, std::string color)
    : Shape(color), pos(pos), text(text) {}

Position2D Text::getPos() const {
    return pos;
}

std::string Text::getText() const {
    return text;
}

void Text::draw() const {
    std::cout << color;
    moveCursor(pos.x, pos.y);
    std::cout << text;
    std::cout << DOS_COLOR;
}

void Text::render(std::vector<std::vector<CanvasCell>>& grid) const {
    int rows = static_cast<int>(grid.size());
    if (rows == 0) return;
    int cols = static_cast<int>(grid[0].size());

    if (pos.y >= 0 && pos.y < rows) {
        for (size_t i = 0; i < text.length(); ++i) {
            int cx = pos.x + static_cast<int>(i);
            if (cx >= 0 && cx < cols) {
                grid[pos.y][cx] = {std::string(1, text[i]), color};
            }
        }
    }
}

std::string Text::serialize() const {
    return "TEXT " + std::to_string(pos.x) + " " + std::to_string(pos.y) + " " + color + " " + text;
}
