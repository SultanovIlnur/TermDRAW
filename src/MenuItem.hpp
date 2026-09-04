#pragma once

#include <string>
#include <vector>

struct MenuItem {
    std::string caption;
    void (*action)();
};

struct MenuSection {
    std::string title;
    std::vector<MenuItem> items;
};