#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "MenuItem.hpp"
#include "ToolbarButton.hpp"
#include "Focus.hpp"
#include "Input.hpp"

class Toolbar {
    public: 
        Toolbar();
        std::vector<ToolbarButton> buttons;
        
        void draw(Focus currentFocus);

        void initMenu();

        bool handleInput(SpecialKey key);

    private:
        std::vector<MenuSection> menus;
        bool activeMenu = false;
        bool activeSubMenu = false;
        int selectedButton = 0;
        int selectedSubMenuButton = 0;
};