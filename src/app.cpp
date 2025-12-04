#include <iostream>
#include "utils.h"
#include "app.h"
#include "utils.h"
#include "shader.h"

namespace glvis {

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

        glfwSetWindowUserPointer(window, this);
        
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        glfwSetCursorPosCallback(window, mouse_callback);  
        glfwSetMouseButtonCallback(window, mouse_button_callback);
        glfwSetScrollCallback(window, scroll_callback);

        return window;
    }

    void App::mainLoop() {

        Shader shader("shaders/simple.vert", "shaders/simple.frag");
        Shader screenShader("shaders/fbo.vert", "shaders/fbo.frag");

        float triangleVertices[] = {
            // positions        // colors
            0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
            0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f
        };
        unsigned int triangleIndices[] = {
            0, 1, 2,
        };

        // triangle
        unsigned int triangleVBO;
        glGenBuffers(1, &triangleVBO);
        unsigned int triangleVAO;
        glGenVertexArrays(1, &triangleVAO);
        unsigned int triangleEBO;
        glGenBuffers(1, &triangleEBO);
        glBindVertexArray(triangleVAO);
        glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangleEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(triangleIndices), triangleIndices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        screenRectangle = std::make_unique<Rectangle>(1000.0, 1000.0);

        // screen FBO
        glGenFramebuffers(1, &screenFBO);
        glBindFramebuffer(GL_FRAMEBUFFER, screenFBO);

        // screen texture
        glGenTextures(1, &screenQuadTexture);
        glBindTexture(GL_TEXTURE_2D, screenQuadTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, screenQuadTexture, 0);

        while (!glfwWindowShouldClose(window)) {

            glBindFramebuffer(GL_FRAMEBUFFER, screenFBO);
            glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            glViewport(0, 0, currentWindowWidth, currentWindowHeight);

            glm::mat4 view = getViewMatrix();
            glm::mat4 projection = glm::mat4(1.0f);
            projection = glm::ortho(0.0f, (float)currentWindowWidth, 0.0f, (float)currentWindowHeight, -1.0f, 1.0f);

            {
                glm::mat4 modelMatrix = glm::mat4(1.0f);
                modelMatrix = glm::scale(modelMatrix, glm::vec3(100.0f, 100.0f, 1.0f));
                shader.use();
                shader.setMat4("model", modelMatrix);
                shader.setMat4("view", view);
                shader.setMat4("projection", projection);
                glBindVertexArray(triangleVAO);
                glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
            }

            {
                glm::mat4 modelMatrix = glm::mat4(1.0f);
                modelMatrix = glm::translate(modelMatrix, glm::vec3(200.0f, 0.0f, 0.0f));
                modelMatrix = glm::scale(modelMatrix, glm::vec3(100.0f, 100.0f, 1.0f));
                shader.setMat4("model", modelMatrix);
                glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
            }

            glBindFramebuffer(GL_FRAMEBUFFER, 0);

            // render quad with framebuffer to screen
            glViewport(0, 0, currentWindowWidth, currentWindowHeight);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            screenShader.use();
            glBindTexture(GL_TEXTURE_2D, screenQuadTexture);
            screenShader.setInt("screenTexture", 0);
            screenRectangle->render();

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

    void App::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
        if (App* app = static_cast<App*>(glfwGetWindowUserPointer(window))) {
            app->processWindowSize(width, height);
        }
    }

    void App::mouse_callback(GLFWwindow *window, double xpos, double ypos) {
        if (App* app = static_cast<App*>(glfwGetWindowUserPointer(window))) {
            app->processMouse(xpos, ypos);
        }
    }

    void App::mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
        if (App* app = static_cast<App*>(glfwGetWindowUserPointer(window))) {
            app->processMousePress(button, action, mods);
        }
    }

    void App::scroll_callback(GLFWwindow *window, double x, double y) {
        if (App* app = static_cast<App*>(glfwGetWindowUserPointer(window))) {
            app->processMouseScroll(x, y);
        }
    }

    void App::processWindowSize(int width, int height) {
        currentWindowWidth = width;
        currentWindowHeight = height;

        // resize screen texture
        glBindFramebuffer(GL_FRAMEBUFFER, screenFBO);
        resizeTexture(screenQuadTexture, width, height);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
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

    void App::processMouseScroll(double x, double y) {
        double zoomFactor = pow(CAMERA_ZOOM_FACTOR, y);
        camera.zoom *= zoomFactor;
        camera.pos.x = (camera.pos.x - mouseXWorld) / zoomFactor + mouseXWorld;
        camera.pos.y = (camera.pos.y - mouseYWorld) / zoomFactor + mouseYWorld;
    }

    void App::processMouseLeftPress(int x, int y) {
        glm::dvec2 worldPos = screenToWorld(x, y);
        std::cout << std::format("Screen: ({}, {}) World: ({}, {})", x, y, worldPos.x, worldPos.y) << std::endl;
    }

    void App::processMouseRightPress(int x, int y) {
    }

    void App::resizeTexture(GLuint textureId, int newWidth, int newHeight) {
        glBindTexture(GL_TEXTURE_2D, textureId);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, newWidth, newHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    App::App() {
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

}
