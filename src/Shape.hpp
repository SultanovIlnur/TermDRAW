#pragma once

class Shape {
    public:
        virtual ~Shape() = default;
        virtual void draw() const = 0;
};