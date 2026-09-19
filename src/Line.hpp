#pragma once

#include "Shape.hpp"
#include "Screen.hpp"
#include <string>
#include <vector>

class Line : public Shape {
    public:
        Line(Position2D start, Position2D end, std::string color = "\033[93m");

        void draw() const override;
        void render(std::vector<std::vector<CanvasCell>>& grid) const override;
        std::string serialize() const override;

        Position2D getStart() const;
        Position2D getEnd() const;

    private:
        Position2D start;
        Position2D end;
};
