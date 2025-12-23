#include "color.h"

namespace glvis {

    Color::Color() {
        r = 0;
        g = 0;
        b = 0;
        a = 255;
    }

    Color::Color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a) {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }

}
