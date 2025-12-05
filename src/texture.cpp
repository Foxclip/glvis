#include "texture.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace glvis {

    Texture::Texture(int width, int height) {
        createEmptyTexture(width, height);
    }

    Texture::Texture(const std::filesystem::path &path) {
        try {
            glGenTextures(1, &ID);
            glBindTexture(GL_TEXTURE_2D, ID);
            int width, height, nrChannels;
            unsigned char* data = stbi_load(path.string().c_str(), &width, &height, &nrChannels, 0);
            if (data) {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            } else {
                throw std::runtime_error("Failed to load texture: " + path.string() + "\n");;
            }
            stbi_image_free(data);
            glBindTexture(GL_TEXTURE_2D, 0);
        } catch (std::exception& e) {
            throw std::runtime_error(__FUNCTION__": " + std::string(e.what()));
        }
    }

    const std::filesystem::path& Texture::getPath() const {
        return path;
    }
}
