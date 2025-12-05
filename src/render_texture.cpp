#include "render_texture.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace glvis {

    RenderTexture::RenderTexture(int width, int height) {
        glGenFramebuffers(1, &FBO);
        glBindFramebuffer(GL_FRAMEBUFFER, FBO);
        createEmptyTexture(width, height);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ID, 0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    RenderTexture::~RenderTexture() {
        glDeleteFramebuffers(1, &FBO);
    }

    unsigned int RenderTexture::getFBO() const {
        return FBO;
    }

    void RenderTexture::resize(int newWidth, int newHeight) {
        glBindFramebuffer(GL_FRAMEBUFFER, FBO);
        resizeTexture(newWidth, newHeight);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}
