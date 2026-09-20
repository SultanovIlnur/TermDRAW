#include "Input.hpp"

KeyEvent readKey() {
    char c;
    if (read(STDIN_FILENO, &c, 1) <= 0) {
        return {SpecialKey::KEY_UNKNOWN, '\0'};
    }
    switch (c) {
        case '\n':
            return {SpecialKey::KEY_ENTER, '\n'};
        case '\033': {
            int bytesWaiting = 0;
            ioctl(STDIN_FILENO, FIONREAD, &bytesWaiting);
            if (bytesWaiting == 0) {
                return {SpecialKey::KEY_ESC, '\033'};
            }
            char nextChar = '\0';
            if (read(STDIN_FILENO, &nextChar, 1) <= 0) {
                return {SpecialKey::KEY_ESC, '\033'};
            }
            char arrowKey = '\0';
            if (read(STDIN_FILENO, &arrowKey, 1) <= 0) {
                return {SpecialKey::KEY_UNKNOWN, '\0'};
            }
            switch (arrowKey) {
                case 'A':
                    return {SpecialKey::ARROW_KEY_UP, '\0'};
                case 'B':
                    return {SpecialKey::ARROW_KEY_DOWN, '\0'};
                case 'C':
                    return {SpecialKey::ARROW_KEY_RIGHT, '\0'};
                case 'D':
                    return {SpecialKey::ARROW_KEY_LEFT, '\0'};
                default:
                    return {SpecialKey::KEY_UNKNOWN, '\0'};
            }
        }
        case '\t':
            return {SpecialKey::KEY_TAB, '\t'};
        case 'q':
        case 'Q':
            return {SpecialKey::KEY_Q, c};
        case 'c':
        case 'C':
            return {SpecialKey::KEY_C, c};
        case '\b':
        case '\177':
            return {SpecialKey::KEY_BACKSPACE, '\b'};
        default:
            if (c >= 32 && c <= 126) {
                return {SpecialKey::KEY_CHAR, c};
            }
            return {SpecialKey::KEY_UNKNOWN, c};
    }
}