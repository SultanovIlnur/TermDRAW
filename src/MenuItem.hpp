#pragma once

#include <string>
#include <vector>
#include "Panel.hpp"

#include <iostream>

struct MenuItem {
    std::string caption;
    void (*action)();
};

struct MenuSection {
    std::string caption;
    std::vector<MenuItem> items;
};

void actionShutdown();