#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

class App {

public:
    App();
    ~App();

private:
    GLFWwindow* window = nullptr;

    GLFWwindow* init();
    void mainLoop();

};
