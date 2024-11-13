#include "Utils.h"
#include <iostream>

namespace Utils {
    void logError(const std::string& message) {
        std::cerr << "Error: " << message << std::endl;
    }
}
