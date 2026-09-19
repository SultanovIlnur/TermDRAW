#pragma once

#include <vector>
#include <string>
#include "../Types.hpp"

class ImageExporter {
    public:
        static bool exportToFile(const std::vector<std::vector<CanvasCell>>& grid,
                                 const std::string& filename,
                                 const std::string& format);
};

