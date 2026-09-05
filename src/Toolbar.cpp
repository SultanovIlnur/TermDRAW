#include "Toolbar.hpp"

Toolbar::Toolbar() {
}

void Toolbar::draw() {
    std::cout << "Toolbar: ";
    for (const auto& button : buttons) {
        std::cout << "[" << button.caption << "] ";
    }
    std::cout << std::endl;
}

void Toolbar::addMenu(const MenuSection& section) {
    
}