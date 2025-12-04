#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "rectangle.h"

namespace glvis {

    const int DEFAULT_WINDOW_WIDTH = 800;
    const int DEFAULT_WINDOW_HEIGHT = 600;
    const double CAMERA_ZOOM_FACTOR = 1.2;

    struct Camera {
        glm::dvec2 pos = glm::dvec2(0.0f, 100.0f);
        double zoom = 1.0f;
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
        double mouseXWorld = 0.0;
        double mouseYWorld = 0.0;
        bool firstMouse = true;
        bool leftMousePressed = false;
        bool rightMousePressed = false;
        std::unique_ptr<Rectangle> screenRectangle = nullptr;
        std::vector<std::unique_ptr<Shape>> shapes;
        unsigned int screenFBO = 0;
        unsigned int screenQuadTexture = 0;

        GLFWwindow* init();
        void mainLoop();
        glm::mat4 getViewMatrix();
        glm::mat4 getInvViewMatrix();
        glm::dvec2 worldToScreen(double x, double y);
        glm::dvec2 screenToWorld(int x, int y);
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
