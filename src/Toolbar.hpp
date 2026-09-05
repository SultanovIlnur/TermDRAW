#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "MenuItem.hpp"
#include "ToolbarButton.hpp"

class Toolbar {
    public: 
        Toolbar();
        std::vector<ToolbarButton> buttons;
        
        void draw();

        void addMenu(const MenuSection& section);
};