#pragma once

#include <string>

#include "../Types.hpp"
#include "Screen.hpp"

class Panel {
    public:
        Panel(Position2D start, Position2D end, std::string color, int layerValue);
        void draw();

    private:
        Layer layer;
        Position2D startPos;
        Position2D endPos;
        std::string color;
};