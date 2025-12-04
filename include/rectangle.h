#pragma once

#include "vector.h"
#include "shape.h"

namespace glvis {
    
    class Texture;

    class Rectangle : public Shape {
    public:
        Rectangle(float width, float height);
        float getWidth() const;
        float getHeight() const;
        Vector2 getSize() const;
        void setTexture(Texture* texture);
        void render(const glm::mat4& view, const glm::mat4& projection) const override;

    private:
        Texture* texture = nullptr;
        float width = 0.0f;
        float height = 0.0f;
        unsigned int VAO = 0;
        unsigned int VBO = 0;
        unsigned int EBO = 0;

    };

}
