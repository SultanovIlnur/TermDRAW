#include "Canvas.hpp"
#include "Input.hpp"
#include "Rectangle.hpp"
#include "Screen.hpp"
#include <memory>

Canvas::Canvas() : cursorPos{10,5} {} // default cursor position

void Canvas::addShape(std::unique_ptr<Shape> shape) {
    shapes.push_back(std::move(shape));
}

void Canvas::clear() {
    shapes.clear();
}

void Canvas::draw() const {
    for (const auto& shape : shapes) {
        shape->draw();
    }

    moveCursor(cursorPos.x, cursorPos.y);
    std::cout << "\033[7m \033[27m"; // cursor of symbol represented as a reversed color square
}

Position2D Canvas::getCursor() const {
    return cursorPos;
}

void Canvas::moveCursorBy(int dx, int dy) {
    cursorPos.x += dx;
    cursorPos.y += dy;
}

bool Canvas::handleInput(SpecialKey key) {
    switch (key) {
        case SpecialKey::ARROW_KEY_UP:
            moveCursorBy(0, -1);
            return true;
        case SpecialKey::ARROW_KEY_DOWN:
            moveCursorBy(0, 1);
            return true;
        case SpecialKey::ARROW_KEY_LEFT:
            moveCursorBy(-1, 0);
            return true;
        case SpecialKey::ARROW_KEY_RIGHT:
            moveCursorBy(1, 0);
            return true;

        case SpecialKey::KEY_ENTER:
            addShape(std::make_unique<Rectangle>(cursorPos, 12, 6));
            return true;

        default:
            return false;
    }
}