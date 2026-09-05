#include "Focus.hpp"

std::string getCurrentMode(Focus currentFocus) {
        switch (currentFocus) {
                case Focus::None:
                return "NONE";
                case Focus::Toolbar:
                return "TOOLBAR";
                case Focus::MenuPopup:
                return "MENU POPUP";
                case Focus::Canvas:
                return "CANVAS";
                default:
                return "UNKNOWN";
        }
}