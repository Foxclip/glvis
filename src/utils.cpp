#include "utils.h"

namespace glvis {

    std::string file_to_str(const std::filesystem::path& path) {
        if (!std::filesystem::exists(path)) {
            throw std::format("File not found: {}", path.string());
        }
        std::ifstream t(path);
        std::stringstream buffer;
        buffer << t.rdbuf();
        return buffer.str();
    }

}
