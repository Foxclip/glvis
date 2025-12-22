#include "rectangle.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include "common.h"
#include "texture.h"

namespace glvis {

    Rectangle::Rectangle(float width, float height) {
        this->width = width;
        this->height = height;
        this->shader = common::defaultShader;

        const float quadVertices[] = {
            // positions   // texture Coords
            0.0f,  height, 0.0f, 1.0f,
            0.0f,  0.0f,   0.0f, 0.0f,
            width, height, 1.0f, 1.0f,
            width, 0.0f,   1.0f, 0.0f
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
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    Rectangle::~Rectangle() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
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

    void Rectangle::setTexture(AbstractTexture* texture) {
        this->texture = texture;
    }

    void Rectangle::render(const glm::mat4& view, const glm::mat4& projection) const {
        try {
            if (shader == nullptr) throw std::runtime_error("Shader not set");
            glm::mat4 modelMatrix = glm::mat4(1.0f);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(position.x, position.y, 0.0f));
            modelMatrix = glm::rotate(modelMatrix, rotation.asRadians(), glm::vec3(0.0f, 0.0f, -1.0f));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(scale.x, scale.y, 1.0f));
            modelMatrix = glm::translate(modelMatrix, glm::vec3(-origin.x, -origin.y, 0.0f));
            shader->use();
            shader->setMat4("model", modelMatrix);
            shader->setMat4("view", view);
            shader->setMat4("projection", projection);
            shader->setVec4("color", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
            if (texture) {
                shader->setInt("tex", 0);
                shader->setBool("hasTexture", true);
                texture->bind();
            } else {
                shader->setInt("tex", -1);
                shader->setBool("hasTexture", false);
            }
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        } catch (std::exception& e) {
            throw std::runtime_error(__FUNCTION__": " + std::string(e.what()));
        }
    }
}
