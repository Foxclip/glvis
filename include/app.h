#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "rectangle.h"
#include "texture.h"

namespace glvis {

    const int DEFAULT_WINDOW_WIDTH = 800;
    const int DEFAULT_WINDOW_HEIGHT = 600;
    const float CAMERA_ZOOM_FACTOR = 1.2f;

    struct Camera {
        glm::vec2 pos = glm::vec2(0.0f, 0.0f);
        float zoom = 1.0f;
    };

    class App {

    public:
        App();
        ~App();

    private:
        GLFWwindow* window = nullptr;
        int currentWindowWidth = DEFAULT_WINDOW_WIDTH;
        int currentWindowHeight = DEFAULT_WINDOW_HEIGHT;
        Camera camera;
        int mouseX = 0;
        int mouseY = 0;
        float mouseXWorld = 0.0f;
        float mouseYWorld = 0.0f;
        bool firstMouse = true;
        bool leftMousePressed = false;
        bool rightMousePressed = false;
        std::unique_ptr<Rectangle> screenRectangle = nullptr;
        std::vector<std::unique_ptr<Shape>> shapes;
        std::unique_ptr<Shader> defaultShaderUptr = nullptr;
        std::unique_ptr<Shader> screenShaderUptr = nullptr;
        unsigned int screenFBO = 0;
        std::unique_ptr<Texture> screenTextureUptr = nullptr;

        GLFWwindow* init();
        void mainLoop();
        glm::mat4 getViewMatrix();
        glm::mat4 getInvViewMatrix();
        glm::vec2 worldToScreen(float x, float y);
        glm::vec2 screenToWorld(int x, int y);
        static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
        static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
        static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
        static void scroll_callback(GLFWwindow* window, double x, double y);
        void processWindowSize(int width, int height);
        void processMouse(double xpos, double ypos);
        void processMousePress(int button, int action, int mods);
        void processMouseScroll(double x, double y);
        void processMouseLeftPress(int x, int y);
        void processMouseRightPress(int x, int y);
        void resizeTexture(GLuint textureId, int newWidth, int newHeight);

    };

}
