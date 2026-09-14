#pragma once

#include "Shape.hpp"
#include "Screen.hpp"

class Line : public Shape {
    public:
        Line(Position2D start, Position2D end);

        void draw() const override;

        Position2D getStart() const;
        Position2D getEnd() const;

    private:
        Position2D start;
        Position2D end;
};

