#pragma once

#include "vector.h"
#include "shape.h"

namespace glvis {

    class Rectangle : public Shape {
    public:
        Rectangle(float width, float height);
        float getWidth() const;
        float getHeight() const;
        Vector2 getSize() const;
        void render() const override;

    private:
        float width = 0.0f;
        float height = 0.0f;
        unsigned int VAO = 0;
        unsigned int VBO = 0;
        unsigned int EBO = 0;

    };

}
