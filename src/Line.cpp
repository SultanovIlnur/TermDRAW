#include "Line.hpp"
#include <cmath>
#include <iostream>

Line::Line(Position2D start, Position2D end, std::string color)
    : Shape(color), start(start), end(end) {}

Position2D Line::getStart() const {
    return start;
}

Position2D Line::getEnd() const {
    return end;
}

void Line::draw() const {
    int x0 = start.x;
    int y0 = start.y;
    int x1 = end.x;
    int y1 = end.y;

    int dx = std::abs(x1 - x0);
    int dy = std::abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    std::string ch = "─";
    if (dx == 0) {
        ch = "│";
    } else if (dy == 0) {
        ch = "─";
    } else if ((x1 - x0) * (y1 - y0) > 0) {
        ch = "╲";
    } else {
        ch = "╱";
    }

    std::cout << color;
    while (true) {
        moveCursor(x0, y0);
        std::cout << ch;

        if (x0 == x1 && y0 == y1) {
            break;
        }

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
    std::cout << DOS_COLOR;
}

void Line::render(std::vector<std::vector<CanvasCell>>& grid) const {
    int rows = static_cast<int>(grid.size());
    if (rows == 0) return;
    int cols = static_cast<int>(grid[0].size());

    int x0 = start.x;
    int y0 = start.y;
    int x1 = end.x;
    int y1 = end.y;

    int dx = std::abs(x1 - x0);
    int dy = std::abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    std::string ch = "─";
    if (dx == 0) {
        ch = "│";
    } else if (dy == 0) {
        ch = "─";
    } else if ((x1 - x0) * (y1 - y0) > 0) {
        ch = "╲";
    } else {
        ch = "╱";
    }

    while (true) {
        if (y0 >= 0 && y0 < rows && x0 >= 0 && x0 < cols) {
            grid[y0][x0] = {ch, color};
        }

        if (x0 == x1 && y0 == y1) {
            break;
        }

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

std::string Line::serialize() const {
    return "LINE " + std::to_string(start.x) + " " + std::to_string(start.y) + " " +
           std::to_string(end.x) + " " + std::to_string(end.y) + " " + color;
}
