#include "util/loader.h"

#include <fstream>
#include <sstream>
#include <exception>

namespace Util {
std::string LoadTextFile(const std::string &filepath) {
    std::string source;
    std::ifstream stream(filepath, std::ios::in);

    if (stream.is_open()) {
        std::stringstream sstr;
        sstr << stream.rdbuf();
        source = sstr.str();
        stream.close();
    } else {
        throw std::runtime_error("File not found");
    }

    return source;
}
} // namespace Util
