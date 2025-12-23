#pragma once
#include <cstdint>

namespace glvis {
    
    class Color {
    public:
        std::uint8_t r, g, b, a;

        Color();
        Color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a = 255);

    };

}
