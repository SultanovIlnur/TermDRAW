#pragma once

#include <vector>
#include <memory>
#include <string>
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
        bool handleInput(KeyEvent key, Tool currentTool);
        bool getIsDrawing() const;
        bool getIsTyping() const;

        void cycleColor();
        void setColorIndex(int index);
        std::string getCurrentColor() const;
        std::string getCurrentColorName() const;

        bool saveToFile(const std::string& filename) const;
        bool loadFromFile(const std::string& filename);
        bool exportImage(const std::string& filename, const std::string& format) const;

    private:
        std::vector<std::unique_ptr<Shape>> shapes;
        Position2D cursorPos;
        Position2D startPos;
        bool isDrawing;
        bool isTyping;
        std::string currentText;
        Tool currentDrawingTool;
        int currentColorIndex;
};