#pragma once

#include <string>

const std::string CLEAR_SCREEN = "\033[2J";
const std::string RESET        = "\033[0m";
const std::string MOVE_HOME    = "\033[H";
const std::string HIDE_CURSOR  = "\033[?25l";
const std::string SHOW_CURSOR  = "\033[?25h";

const std::string DOS_COLOR = "\033[93;44m";

const int KEY_TAB = 9;
const int KEY_Q = 113;

struct Layer {
    int value;
    bool visibility;
};

struct Position2D {
    int x;
    int y;
};