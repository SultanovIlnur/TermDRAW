#pragma once

#include <string>

enum class Focus {
        None,
        Toolbar,
        MenuPopup,
        Canvas
};

std::string getCurrentMode(Focus currentFocus);