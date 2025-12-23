#pragma once

#include "vector.h"
#include "shape.h"
#include "vertex_buffer.h"

namespace glvis {
    
    class AbstractTexture;

    class Rectangle : public Shape {
    public:
        Rectangle(float width, float height);
        ~Rectangle();
        float getWidth() const;
        float getHeight() const;
        Vector2 getSize() const;
        void setTexture(AbstractTexture* texture);
        void render(const glm::mat4& view, const glm::mat4& projection) const override;

    private:
        AbstractTexture* texture = nullptr;
        float width = 0.0f;
        float height = 0.0f;
        VertexBuffer vertexBuffer;

    };

}
