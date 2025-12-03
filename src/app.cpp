#include <iostream>
#include "utils.h"
#include "app.h"
#include "utils.h"
#include "shader.h"

App* app = nullptr;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    app->processWindowSize(width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    app->processMouse(xpos, ypos);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    app->processMousePress(button, action, mods);
}

void scroll_callback(GLFWwindow* window, double x, double y) {
    app->processScroll(x, y);
}

GLFWwindow* App::init() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return nullptr;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Simple GLFW Window", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return nullptr;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);  
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, scroll_callback);

    return window;
}

void App::processWindowSize(int width, int height) {
    currentWindowWidth = width;
    currentWindowHeight = height;
    glViewport(0, 0, width, height);
}

void App::processMouse(double xpos, double ypos) {
    if (firstMouse) {
        mouseX = (int)xpos;
        mouseY = (int)ypos;
        mouseXWorld = screenToWorld(mouseX, mouseY).x;
        mouseYWorld = screenToWorld(mouseX, mouseY).y;
        firstMouse = false;
    }
    double xoffset = xpos - mouseX;
    double yoffset = ypos - mouseY;
    if (rightMousePressed) {
        camera.pos.x -= xoffset / camera.zoom;
        camera.pos.y -= yoffset / camera.zoom;
    }
    mouseX = (int)xpos;
    mouseY = (int)ypos;
    mouseXWorld = screenToWorld(mouseX, mouseY).x;
    mouseYWorld = screenToWorld(mouseX, mouseY).y;
}

void App::processMousePress(int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        leftMousePressed = true;
        processMouseLeftPress(mouseX, mouseY);
    } else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        leftMousePressed = false;
    } else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        rightMousePressed = true;
        processMouseRightPress(mouseX, mouseY);
    } else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
        rightMousePressed = false;
    }
}

void App::processScroll(double x, double y) {
    double zoomFactor = pow(CAMERA_ZOOM_FACTOR, y);
    camera.zoom *= zoomFactor;
    camera.pos.x = (camera.pos.x - mouseXWorld) / zoomFactor + mouseXWorld;
    camera.pos.y = (camera.pos.y - mouseYWorld) / zoomFactor + mouseYWorld;
}

void App::mainLoop() {

    Shader shader("shaders/simple.vert", "shaders/simple.frag");

    float vertices[] = {
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f
    };
    unsigned int indices[] = {
        0, 1, 2,
    };

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

        glm::mat4 view = getViewMatrix();
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::ortho(0.0f, (float)currentWindowWidth, 0.0f, (float)currentWindowHeight, -1.0f, 1.0f);

        {
            glm::mat4 modelMatrix = glm::mat4(1.0f);
            modelMatrix = glm::scale(modelMatrix, glm::vec3(100.0f, 100.0f, 1.0f));
            // modelMatrix = glm::rotate(modelMatrix, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
            shader.setMat4("model", modelMatrix);
            shader.setMat4("view", view);
            shader.setMat4("projection", projection);
            shader.use();
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }

        {
            glm::mat4 modelMatrix = glm::mat4(1.0f);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(200.0f, 0.0f, 0.0f));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(100.0f, 100.0f, 1.0f));
            shader.setMat4("model", modelMatrix);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

glm::mat4 App::getViewMatrix() {
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(currentWindowWidth / 2, currentWindowHeight / 2, 0.0f));
    view = glm::scale(view, glm::vec3(camera.zoom, -camera.zoom, 1.0f));
    view = glm::translate(view, glm::vec3(-camera.pos.x, -camera.pos.y, 0.0f));
    return view;
}

glm::mat4 App::getInvViewMatrix() {
    glm::mat4 invView = glm::mat4(1.0f);
    invView = glm::translate(invView, glm::vec3(camera.pos.x, camera.pos.y, 0.0f));
    invView = glm::scale(invView, glm::vec3(1.0f / camera.zoom, -1.0f / camera.zoom, 1.0f));
    invView = glm::translate(invView, glm::vec3(-currentWindowWidth / 2, -currentWindowHeight / 2, 0.0f));
    return invView;
}

glm::dvec2 App::worldToScreen(double x, double y) {
    glm::mat4 view = getViewMatrix();
    glm::dvec4 point = view * glm::dvec4(x, y, 0.0, 1.0);
    glm::dvec2 result = glm::dvec2(point.x, currentWindowHeight - point.y);
    return result;
}

glm::dvec2 App::screenToWorld(int x, int y) {
    glm::mat4 invView = getInvViewMatrix();
    glm::dvec4 point = invView * glm::dvec4(x, currentWindowHeight - y, 0.0, 1.0);
    glm::dvec2 result = glm::dvec2(point.x, point.y);
    return result;
}

void App::processMouseLeftPress(int x, int y) {
    glm::dvec2 worldPos = screenToWorld(x, y);
    std::cout << std::format("Screen: ({}, {}) World: ({}, {})", x, y, worldPos.x, worldPos.y) << std::endl;
}

void App::processMouseRightPress(int x, int y) {
}

App::App() {
    app = this;
    window = init();
    if (!window) {
        throw std::runtime_error("Failed to initialize GLFW window");
    }
    mainLoop();
}

App::~App() {
    glfwDestroyWindow(window);
    glfwTerminate();
}
