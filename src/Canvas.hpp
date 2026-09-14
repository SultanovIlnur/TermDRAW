#pragma once

#include <vector>
#include <memory>
#include "../Types.hpp"
#include "Input.hpp"
#include "Shape.hpp"
#include "Toolbox.hpp"

class Canvas {
    public:
        Canvas();

        void addShape(std::unique_ptr<Shape> shape);
        void clear();
        void draw() const;

        Position2D getCursor() const;
        void moveCursorBy(int dx, int dy);
        bool handleInput(SpecialKey key, Tool currentTool);
        bool getIsDrawing() const;

    private:
        std::vector<std::unique_ptr<Shape>> shapes;
        Position2D cursorPos;
        Position2D startPos;
        bool isDrawing;
        Tool currentDrawingTool;
};