#pragma once

#include "Shape.hpp"
#include "Screen.hpp"
#include <string>
#include <vector>

class Rectangle : public Shape {
    public:
        Rectangle(Position2D pos, int width, int height, std::string color = "\033[93m");

        void draw() const override;
        void render(std::vector<std::vector<CanvasCell>>& grid) const override;
        std::string serialize() const override;

    private:
        Position2D pos;
        int width;
        int height;
};