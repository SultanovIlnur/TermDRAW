#pragma once

#include <vector>
#include <memory>
#include "../Types.hpp"
#include "Input.hpp"
#include "Shape.hpp"

class Canvas {
    public:
        Canvas();

        void addShape(std::unique_ptr<Shape> shape);
        void clear();
        void draw() const;

        // moving the painting cursor on ui
        Position2D getCursor() const;
        void moveCursorBy(int dx, int dy);
        void handleInput(SpecialKey key);

    private:
        std::vector<std::unique_ptr<Shape>> shapes;
        Position2D cursorPos;

};