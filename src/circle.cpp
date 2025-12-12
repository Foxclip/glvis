#include "circle.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <corecrt_math_defines.h>
#include "common.h"
#include "texture.h"
#include "shader.h"
#include <iostream>

namespace glvis {

    Circle::Circle(float radius, size_t numSegments) {
        this->radius = radius;
        this->numSegments = numSegments;
        this->shader = common::defaultShader;

        float theta = (float)(2.0 * M_PI / numSegments);
        std::vector<float> vertices;
        std::vector<unsigned int> indices;
        vertices.push_back(0.0f + radius);
        vertices.push_back(0.0f + radius);
        vertices.push_back(0.0f);
        vertices.push_back(0.5f);
        vertices.push_back(0.5f);
        for (size_t i = 0; i < numSegments; i++) {
            float x = radius * cos(theta * i) + radius;
            float y = radius * sin(theta * i) + radius;
            float texX = (x / radius + 1.0f) / 2.0f;
            float texY = (y / radius + 1.0f) / 2.0f;
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(0.0f);
            vertices.push_back(texX);
            vertices.push_back(texY);
        }
        for (size_t i = 0; i < numSegments - 1; i++) {
            indices.push_back(0);
            indices.push_back((int)i + 1);
            indices.push_back((int)i + 2);
        }
        indices.push_back(0);
        indices.push_back((int)numSegments);
        indices.push_back(1);

        glGenBuffers(1, &VBO);
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &EBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    Circle::~Circle() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }

    void Circle::render(const glm::mat4& view, const glm::mat4& projection) const {
        try {
            if (shader == nullptr) throw std::runtime_error("Shader not set");
            glm::mat4 modelMatrix = glm::mat4(1.0f);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(position.x, position.y, 0.0f));
            modelMatrix = glm::rotate(modelMatrix, rotation, glm::vec3(0.0f, 0.0f, -1.0f));
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
            glDrawElements(GL_TRIANGLES, (int)numSegments * 3, GL_UNSIGNED_INT, 0);
        } catch (std::exception& e) {
            throw std::runtime_error(__FUNCTION__": " + std::string(e.what()));
        }
    }
}
