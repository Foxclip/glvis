#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const int DEFAULT_WINDOW_WIDTH = 800;
const int DEFAULT_WINDOW_HEIGHT = 600;

extern int currentWindowWidth;
extern int currentWindowHeight;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

struct Camera {
    glm::vec2 pos = glm::vec2(100.0f, 0.0f);
    float zoom = 1.0f;
};

class App {

public:
    App();
    ~App();

private:
    GLFWwindow* window = nullptr;
    Camera camera;

    GLFWwindow* init();
    void mainLoop();

};
