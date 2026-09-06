#pragma once

#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "../Types.hpp"

void moveCursor(int x, int y);

Position2D getTerminalSize();

void init();

void shutdown();