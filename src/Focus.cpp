#include "Focus.hpp"

std::string getCurrentMode(Focus currentFocus) {
        switch (currentFocus) {
                case Focus::None:
                return "None";
                case Focus::Toolbar:
                return "Toolbar";
                case Focus::MenuPopup:
                return "MenuPopup";
                case Focus::Canvas:
                return "Canvas";
                default:
                return "Unknown";
        }
}