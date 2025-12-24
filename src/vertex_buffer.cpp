#include "vertex_buffer.h"
#include <stdexcept>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "vertex.h"

namespace glvis {

    VertexBuffer::VertexBuffer() {
        VBO = 0;
        VAO = 0;
    }

    VertexBuffer::~VertexBuffer() {
        if (VAO != 0) {
            glDeleteVertexArrays(1, &VAO);
            VAO = 0;
        }
        if (VBO != 0) {
            glDeleteBuffers(1, &VBO);
            VBO = 0;
        }
    }

bool VertexBuffer::create(std::size_t vertexCount) {
        glGenBuffers(1, &VBO);
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex), nullptr, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        
        this->vertices.resize(vertexCount);
        return true;
    }

    std::size_t VertexBuffer::getVertexCount() const {
        return vertices.size();
    }

    bool VertexBuffer::update(const std::vector<Vertex>& newVertices) {
        if (newVertices.size() == this->vertices.size()) {
            this->vertices = newVertices;
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, newVertices.size() * sizeof(Vertex), newVertices.data());
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        } else {
            if (VBO != 0) {
                glDeleteBuffers(1, &VBO);
                VBO = 0;
            }
            this->vertices = newVertices;
            glGenBuffers(1, &VBO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, newVertices.size() * sizeof(Vertex), newVertices.data(), GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
        return true;
    }

    PrimitiveType VertexBuffer::getPrimitiveType() const {
        return type;
    }

    void VertexBuffer::setPrimitiveType(PrimitiveType type) {
        this->type = type;
    }
    
    unsigned int VertexBuffer::getVAO() const {
        return VAO;
    }
}
