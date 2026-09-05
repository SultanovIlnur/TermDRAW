#pragma once

#include <string>
#include <vector>
#include "Panel.hpp"

struct MenuItem {
    std::string caption;
    void (*action)();
};

struct MenuSection {
    std::string caption;
    std::vector<MenuItem> items;
};