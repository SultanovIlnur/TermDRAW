#pragma once

#include <functional>
#include <string>
#include <vector>
#include "Panel.hpp"

#include <iostream>

struct MenuItem {
    std::string caption;
    std::function<void()> action;
};

struct MenuSection {
    std::string caption;
    std::vector<MenuItem> items;
};

void actionNewFile();

void actionShutdown();