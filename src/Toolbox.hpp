#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "../Types.hpp"
#include "Input.hpp"
#include "Toolbox.hpp"
#include "Panel.hpp"
#include "Screen.hpp"

enum class Tool {
    Rectangle,
    Line,
    Circle
};

struct ToolItem {
    Tool tool;
    std::string icon;
};

class Toolbox {
    public:
        Toolbox();
        void draw(bool isFocused) const;
        bool handleInput(SpecialKey key);
        Tool getSelectedTool() const;
    private:
        std::vector<ToolItem> tools;
        int selectedIndex;
};