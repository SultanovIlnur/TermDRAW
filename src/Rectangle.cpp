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

std::string Rectangle::serialize() const {
    return "RECT " + std::to_string(pos.x) + " " + std::to_string(pos.y) + " " +
           std::to_string(width) + " " + std::to_string(height) + " " + color;
}