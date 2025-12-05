#include "abstract_texture.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace glvis {

    int AbstractTexture::getID() const {
        return ID;
    }

    int AbstractTexture::getWidth() const {
        return width;
    }

    int AbstractTexture::getHeight() const {
        return height;
    }

    void AbstractTexture::bind() {
        glBindTexture(GL_TEXTURE_2D, ID);
    }

    void AbstractTexture::unbind() {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void AbstractTexture::resize(int newWidth, int newHeight) {
        resizeTexture(newWidth, newHeight);
    }

    AbstractTexture::~AbstractTexture() {
        glDeleteTextures(1, &ID);
    }

    void AbstractTexture::createEmptyTexture(int width, int height) {
        glGenTextures(1, &ID);
        glBindTexture(GL_TEXTURE_2D, ID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void AbstractTexture::resizeTexture(int newWidth, int newHeight) {
        glBindTexture(GL_TEXTURE_2D, ID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, newWidth, newHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
