#pragma once

#include <functional>
#include <string>
#include <vector>
#include "../Types.hpp"
#include "Panel.hpp"
#include "Input.hpp"
#include "Screen.hpp"

struct DialogButton {
    std::string caption;
    std::function<void()> action;
};

class Dialog {
    public:
        Dialog(int width, int height, const std::string& title);

        void addLine(const std::string& line);
        void addButton(const std::string& caption, std::function<void()> action);
        void draw() const;
        bool shouldClose() const;
        bool handleInput(SpecialKey key);

        bool isVisible() const;
        void open();
        void close();

    private:
        int width;
        int height;
        std::string title;
        std::vector<std::string> lines;

        std::vector<DialogButton> buttons;
        int selectedButton = 0;
        bool needClose = false;
};