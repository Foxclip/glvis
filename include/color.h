#pragma once
#include <cstdint>

namespace glvis {
    
    class Color {
    public:
        float r = 0.0f;
        float g = 0.0f;
        float b = 0.0f;
        float a = 1.0f;

        Color();
        Color(float r, float g, float b, float a = 1.0f);

    };

}
