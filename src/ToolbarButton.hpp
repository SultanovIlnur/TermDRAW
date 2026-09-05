#pragma once
#include "../Types.hpp"
#include "Screen.hpp"

#include <string>

class ToolbarButton {
    public:
        ToolbarButton(Layer layer, const std::string& caption) : layer(layer), caption(caption) {}
        Layer layer;
        std::string caption;
};