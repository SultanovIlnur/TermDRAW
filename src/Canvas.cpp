#include "Canvas.hpp"
#include "Screen.hpp"

Canvas::Canvas() : cursorPos{10,5} {} // default cursor position

void Canvas::addShape(std::unique_ptr<Shape> shape) {
    shapes.push_back(std::move(shape));
}