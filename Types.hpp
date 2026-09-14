#pragma once

#include <string>
#include <vector>

const std::string CLEAR_SCREEN = "\033[2J";
const std::string RESET        = "\033[0m";
const std::string MOVE_HOME    = "\033[H";
const std::string HIDE_CURSOR  = "\033[?25l";
const std::string SHOW_CURSOR  = "\033[?25h";

const std::string DOS_COLOR = "\033[93;44m";

const int KEY_TAB = 9;
const int KEY_Q = 113;

struct ColorInfo {
    std::string name;
    std::string code;
};

const std::vector<ColorInfo> PALETTE = {
    {"Yellow",  "\033[93m"},
    {"White",   "\033[97m"},
    {"Green",   "\033[92m"},
    {"Cyan",    "\033[96m"},
    {"Red",     "\033[91m"},
    {"Magenta", "\033[95m"}
};

struct Layer {
    int value;
    bool visibility;
};

struct Position2D {
    int x;
    int y;
};