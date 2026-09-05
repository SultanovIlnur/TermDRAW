#include "Input.hpp"

SpecialKey readKey() {
    char c;
    if (read(STDIN_FILENO, &c, 1) <= 0) {
        return SpecialKey::KEY_UNKNOWN;
    }
    switch (c) {
        case '\n':
            return SpecialKey::KEY_ENTER;
        case '\033': {
            int bytesWaiting = 0;
            ioctl(STDIN_FILENO, FIONREAD, &bytesWaiting);
            if (bytesWaiting == 0) {
                return SpecialKey::KEY_ESC;
            }
            std::cin.get(); // skip the '[' character
            char arrowKey = std::cin.get();
            switch (arrowKey) {
                case 'A':
                    return SpecialKey::ARROW_KEY_UP;
                case 'B':
                    return SpecialKey::ARROW_KEY_DOWN;
                case 'C':
                    return SpecialKey::ARROW_KEY_RIGHT;
                case 'D':
                    return SpecialKey::ARROW_KEY_LEFT;
                default:
                    return SpecialKey::KEY_UNKNOWN;
            }
        }
        case '\t':
            return SpecialKey::KEY_TAB;
        case 'q':
        case 'Q':
            return SpecialKey::KEY_Q;
        case '\b':
        case '\177':
            return SpecialKey::KEY_BACKSPACE;
        default:
            return SpecialKey::KEY_UNKNOWN;
    }
}