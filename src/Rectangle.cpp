#include "Rectangle.hpp"

Rectangle::Rectangle(Position2D pos, int width, int height, std::string color)
    : Shape(color), pos(pos), width(width), height(height) {}

void Rectangle::draw() const {
    std::cout << color;
    moveCursor(pos.x, pos.y);
    std::cout << "┌";

    for (int x = 1; x < width - 1; x++) {
        std::cout << "─";
    }

    std::cout << "┐";

    for (int y = 1; y < height - 1; y++) {
        moveCursor(pos.x, pos.y + y);
        std::cout << "│";
        moveCursor(pos.x + width - 1, pos.y + y);
        std::cout << "│";
    }

    moveCursor(pos.x, pos.y + height - 1);
    std::cout << "└";
    for (int x = 1; x < width - 1; x++) {
        std::cout << "─";
    }
    std::cout << "┘";
    std::cout << DOS_COLOR;
}

void Rectangle::render(std::vector<std::vector<CanvasCell>>& grid) const {
    int rows = static_cast<int>(grid.size());
    if (rows == 0) return;
    int cols = static_cast<int>(grid[0].size());

    auto setCell = [&](int x, int y, const std::string& ch) {
        if (y >= 0 && y < rows && x >= 0 && x < cols) {
            grid[y][x] = {ch, color};
        }
    };

    setCell(pos.x, pos.y, "┌");
    for (int x = 1; x < width - 1; x++) {
        setCell(pos.x + x, pos.y, "─");
    }
    setCell(pos.x + width - 1, pos.y, "┐");

    for (int y = 1; y < height - 1; y++) {
        setCell(pos.x, pos.y + y, "│");
        setCell(pos.x + width - 1, pos.y + y, "│");
    }

    setCell(pos.x, pos.y + height - 1, "└");
    for (int x = 1; x < width - 1; x++) {
        setCell(pos.x + x, pos.y + height - 1, "─");
    }
    setCell(pos.x + width - 1, pos.y + height - 1, "┘");
}

std::string Rectangle::serialize() const {
    return "RECT " + std::to_string(pos.x) + " " + std::to_string(pos.y) + " " +
           std::to_string(width) + " " + std::to_string(height) + " " + color;
}