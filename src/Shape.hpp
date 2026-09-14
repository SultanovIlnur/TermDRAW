#pragma once

#include <string>

class Shape {
    public:
        Shape(std::string color = "\033[93m");
        virtual ~Shape() = default;
        virtual void draw() const = 0;
        virtual std::string serialize() const = 0;
        std::string getColor() const;
        void setColor(const std::string& newColor);

    protected:
        std::string color;
};