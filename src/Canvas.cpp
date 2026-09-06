#include "Canvas.hpp"
#include "Screen.hpp"

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