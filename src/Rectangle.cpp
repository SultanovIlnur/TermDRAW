#include "Rectangle.hpp"

Rectangle::Rectangle(Position2D pos, int width, int height) : pos(pos), width(width), height(height) {}

void Rectangle::draw() const {
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
}