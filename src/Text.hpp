#pragma once

#include "Shape.hpp"
#include "Screen.hpp"
#include <string>
#include <vector>

class Text : public Shape {
    public:
        Text(Position2D pos, const std::string& text, std::string color = "\033[93m");

        void draw() const override;
        void render(std::vector<std::vector<CanvasCell>>& grid) const override;
        std::string serialize() const override;

        Position2D getPos() const;
        std::string getText() const;

    private:
        Position2D pos;
        std::string text;
};
