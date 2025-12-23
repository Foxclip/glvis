#pragma once

#include <vector>
#include "common.h"
#include "vertex.h"

namespace glvis {
    
    class VertexBuffer {
    public:
        VertexBuffer();
        ~VertexBuffer();
        bool create(std::size_t vertexCount);
        std::size_t getVertexCount() const;
        bool update(const std::vector<Vertex>& newVertices);
        PrimitiveType getPrimitiveType() const;
        void setPrimitiveType(PrimitiveType type);
        unsigned int getVAO() const;

    private:
        PrimitiveType type = PrimitiveType::Triangles;
        std::vector<Vertex> vertices;
        unsigned int VAO = 0;
        unsigned int VBO = 0;

    };

}
