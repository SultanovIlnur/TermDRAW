#pragma once

#include <string>

enum class Focus {
        None,
        Toolbar, // upper toolbar with buttons (eg. File, Edit, Options, Help and etc)
        MenuPopup, // Popup submenu with option buttons when pressing buttons on toolbar
        Canvas, // Drawing canvas
        Dialog, // Dialog windows (have the most priority)
};

std::string getCurrentMode(Focus currentFocus);