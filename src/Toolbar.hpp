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

        void initMenu();

        bool handleInput(int key);

    private:
        std::vector<MenuSection> menus;
        int activeMenu = -1;
};