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
        
        void draw(bool isFocused);

        void initMenu();

        bool handleInput(int key);

    private:
        std::vector<MenuSection> menus;
        bool activeMenu = false;
        int selectedButton = 0;
};