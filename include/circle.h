#pragma once

#include "shape.h"
#include <glm/glm.hpp>
#include "texture.h"

namespace glvis {

    class Circle : public Shape {
    public:
        Circle(float radius = 0, size_t numSegments = 30);
        ~Circle();
        void render(const glm::mat4& view, const glm::mat4& projection) const override;

    private:
        AbstractTexture* texture = nullptr;
        float radius = 0.0f;
        size_t numSegments = 0;
        unsigned int VAO = 0;
        unsigned int VBO = 0;
        unsigned int EBO = 0;
        
    };

}
