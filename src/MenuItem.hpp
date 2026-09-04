#pragma once

#include <string>
#include <vector>

struct MenuItem {
    std::string caption;
    void (*action)();
};