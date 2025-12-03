#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const int DEFAULT_WINDOW_WIDTH = 800;
const int DEFAULT_WINDOW_HEIGHT = 600;
const double CAMERA_ZOOM_FACTOR = 1.2;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void scroll_callback(GLFWwindow* window, double x, double y);

struct Camera {
    glm::vec2 pos = glm::vec2(100.0f, 0.0f);
    double zoom = 1.0f;
};

class App {

public:
    App();
    ~App();
    void processWindowSize(int width, int height);
    void processMouse(double xpos, double ypos);
    void processMousePress(int button, int action, int mods);
    void processScroll(double x, double y);

private:
    GLFWwindow* window = nullptr;
    int currentWindowWidth = DEFAULT_WINDOW_WIDTH;
    int currentWindowHeight = DEFAULT_WINDOW_HEIGHT;
    Camera camera;
    int mouseLastX = 0;
    int mouseLastY = 0;
    bool firstMouse = true;
    bool leftMousePressed = false;
    bool rightMousePressed = false;

    GLFWwindow* init();
    void mainLoop();

};

extern App* app;
