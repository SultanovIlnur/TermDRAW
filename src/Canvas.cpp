#include "Canvas.hpp"
#include "Input.hpp"
#include "Rectangle.hpp"
#include "Line.hpp"
#include "Screen.hpp"
#include <memory>
#include <algorithm>
#include <cmath>

Canvas::Canvas()
    : cursorPos{10, 5}, startPos{10, 5}, isDrawing(false),
      currentDrawingTool(Tool::Rectangle), currentColorIndex(0) {}

void Canvas::addShape(std::unique_ptr<Shape> shape) {
    shapes.push_back(std::move(shape));
}

void Canvas::clear() {
    shapes.clear();
    isDrawing = false;
}

void Canvas::draw() const {
    Position2D term = getTerminalSize();
    std::cout << "\033[90;44m";
    for (int y = 3; y < term.y - 1; y += 2) {
        for (int x = 10; x < term.x - 1; x += 4) {
            moveCursor(x, y);
            std::cout << "·";
        }
    }
    std::cout << DOS_COLOR;
    for (const auto& shape : shapes) {
        shape->draw();
    }

    if (isDrawing) {
        if (currentDrawingTool == Tool::Rectangle) {
            int left = std::min(startPos.x, cursorPos.x);
            int top = std::min(startPos.y, cursorPos.y);
            int width = std::max(2, std::abs(cursorPos.x - startPos.x) + 1);
            int height = std::max(2, std::abs(cursorPos.y - startPos.y) + 1);
            Rectangle preview({left, top}, width, height, getCurrentColor());
            preview.draw();
        } else if (currentDrawingTool == Tool::Line) {
            Line preview(startPos, cursorPos, getCurrentColor());
            preview.draw();
        }
    }

    moveCursor(cursorPos.x, cursorPos.y);
    std::cout << "\033[7m \033[27m";
}

Position2D Canvas::getCursor() const {
    return cursorPos;
}

void Canvas::moveCursorBy(int dx, int dy) {
    cursorPos.x += dx;
    cursorPos.y += dy;
}

bool Canvas::getIsDrawing() const {
    return isDrawing;
}

void Canvas::cycleColor() {
    currentColorIndex = (currentColorIndex + 1) % PALETTE.size();
}

void Canvas::setColorIndex(int index) {
    if (index >= 0 && index < static_cast<int>(PALETTE.size())) {
        currentColorIndex = index;
    }
}

std::string Canvas::getCurrentColor() const {
    return PALETTE[currentColorIndex].code;
}

std::string Canvas::getCurrentColorName() const {
    return PALETTE[currentColorIndex].name;
}

bool Canvas::handleInput(SpecialKey key, Tool currentTool) {
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

        case SpecialKey::KEY_C:
            cycleColor();
            return true;

        case SpecialKey::KEY_ENTER:
            if (!isDrawing) {
                isDrawing = true;
                startPos = cursorPos;
                currentDrawingTool = currentTool;
            } else {
                if (currentDrawingTool == Tool::Rectangle) {
                    int left = std::min(startPos.x, cursorPos.x);
                    int top = std::min(startPos.y, cursorPos.y);
                    int width = std::max(2, std::abs(cursorPos.x - startPos.x) + 1);
                    int height = std::max(2, std::abs(cursorPos.y - startPos.y) + 1);
                    addShape(std::make_unique<Rectangle>(Position2D{left, top}, width, height, getCurrentColor()));
                } else if (currentDrawingTool == Tool::Line) {
                    addShape(std::make_unique<Line>(startPos, cursorPos, getCurrentColor()));
                }
                isDrawing = false;
            }
            return true;

        case SpecialKey::KEY_ESC:
            if (isDrawing) {
                isDrawing = false;
                return true;
            }
            return false;

        default:
            return false;
    }
}