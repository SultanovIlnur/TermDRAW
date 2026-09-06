
#pragma once
#include "Shape.hpp"
#include "Screen.hpp"

class Rectangle : public Shape {
    public:
        Rectangle(Position2D pos, int width, int height)

        void draw() const override;

    private:
        Position2D pos;
        int width;
        int height;
};