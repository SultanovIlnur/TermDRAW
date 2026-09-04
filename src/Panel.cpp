#include "Panel.hpp"


    Panel::Panel(Position2D start, Position2D end, std::string color, int layerValue)
        : startPos(start), endPos(end), color(color), layer{ layerValue,    true} {}
    
    void Panel::draw() {
            moveCursor(startPos.x, startPos.y);
            std::cout << "+";

            for (int x = startPos.x + 1; x < endPos.x; x++)
                std::cout << "-";

            std::cout << "+";

            for (int y = startPos.y + 1; y < endPos.y; y++)
            {
                moveCursor(startPos.x, y);
                std::cout << "|";

                for (int x = startPos.x + 1; x < endPos.x; x++)
                    std::cout << " ";

                std::cout << "|";
            }

            moveCursor(startPos.x, endPos.y);
            std::cout << "+";

            for (int x = startPos.x + 1; x < endPos.x; x++)
                std::cout << "-";

            std::cout << "+";
        }