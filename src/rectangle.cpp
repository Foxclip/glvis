#include "rectangle.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace glvis {

    Rectangle::Rectangle(float width, float height) {
        this->width = width;
        this->height = height;

        const float quadVertices[] = {
            // positions                 // texture Coords
            -width / 2.0f,  height / 2.0f, 0.0f, 0.0f, 1.0f,
            -width / 2.0f, -height / 2.0f, 0.0f, 0.0f, 0.0f,
             width / 2.0f,  height / 2.0f, 0.0f, 1.0f, 1.0f,
             width / 2.0f, -height / 2.0f, 0.0f, 1.0f, 0.0f
        };

        const unsigned int quadIndices[] = {
            0, 1, 2,
            2, 1, 3
        };

        glGenBuffers(1, &VBO);
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &EBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadIndices), quadIndices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    float Rectangle::getWidth() const {
        return width;
    }

    float Rectangle::getHeight() const {
        return height;
    }

    Vector2 Rectangle::getSize() const {
        return Vector2(width, height);
    }

    void Rectangle::render() const {
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
}
