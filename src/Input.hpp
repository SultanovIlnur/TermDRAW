#pragma once

#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

enum struct SpecialKey {
    KEY_NONE,
    ARROW_KEY_UP,
    ARROW_KEY_DOWN,
    ARROW_KEY_LEFT,
    ARROW_KEY_RIGHT,
    KEY_ENTER,
    KEY_ESC,
    KEY_TAB,
    KEY_Q,
    KEY_BACKSPACE,
    KEY_UNKNOWN
};

SpecialKey readKey();