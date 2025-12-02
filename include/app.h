#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

const int DEFAULT_WINDOW_WIDTH = 800;
const int DEFAULT_WINDOW_HEIGHT = 600;

extern int currentWindowWidth;
extern int currentWindowHeight;
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
