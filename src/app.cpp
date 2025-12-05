#include <iostream>
#include "utils.h"
#include "app.h"
#include "utils.h"
#include "shader.h"
#include "common.h"

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

        defaultShaderUptr = std::make_unique<Shader>("shaders/simple.vert", "shaders/simple.frag");
        common::defaultShader = defaultShaderUptr.get();
        screenShaderUptr = std::make_unique<Shader>("shaders/fbo.vert", "shaders/fbo.frag");

        // screen FBO
        glGenFramebuffers(1, &screenFBO);
        glBindFramebuffer(GL_FRAMEBUFFER, screenFBO);

        // screen texture
        screenTextureUptr = std::make_unique<Texture>(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, screenTextureUptr->getID(), 0);

        screenRectangle = std::make_unique<Rectangle>(2.0f, 2.0f);
        screenRectangle->setShader(screenShaderUptr.get());
        screenRectangle->setTexture(screenTextureUptr.get());

        return window;
    }

    void App::mainLoop() {

        while (!glfwWindowShouldClose(window)) {

            glBindFramebuffer(GL_FRAMEBUFFER, screenFBO);
            glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            glViewport(0, 0, currentWindowWidth, currentWindowHeight);

            glm::mat4 view = getViewMatrix();
            glm::mat4 projection = glm::mat4(1.0f);
            projection = glm::ortho(0.0f, (float)currentWindowWidth, 0.0f, (float)currentWindowHeight, -1.0f, 1.0f);

            for (int i = 0; i < shapes.size(); i++) {
                Shape* shape = shapes[i].get();
                shape->render(view, projection);
            }

            glBindFramebuffer(GL_FRAMEBUFFER, 0);

            // render quad with framebuffer to screen
            glViewport(0, 0, currentWindowWidth, currentWindowHeight);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            screenRectangle->render(view, projection);

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

    glm::vec2 App::worldToScreen(float x, float y) {
        glm::mat4 view = getViewMatrix();
        glm::vec4 point = view * glm::vec4(x, y, 0.0f, 1.0f);
        glm::vec2 result = glm::vec2(point.x, currentWindowHeight - point.y);
        return result;
    }

    glm::vec2 App::screenToWorld(int x, int y) {
        glm::mat4 invView = getInvViewMatrix();
        glm::vec4 point = invView * glm::vec4(x, currentWindowHeight - y, 0.0f, 1.0f);
        glm::vec2 result = glm::vec2(point.x, point.y);
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
        resizeTexture(screenTextureUptr->getID(), width, height);
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
        float xoffset = (float)xpos - mouseX;
        float yoffset = (float)ypos - mouseY;
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
        float zoomFactor = powf(CAMERA_ZOOM_FACTOR, (float)y);
        camera.zoom *= zoomFactor;
        camera.pos.x = (camera.pos.x - mouseXWorld) / zoomFactor + mouseXWorld;
        camera.pos.y = (camera.pos.y - mouseYWorld) / zoomFactor + mouseYWorld;
    }

    void App::processMouseLeftPress(int x, int y) {
        glm::vec2 worldPos = screenToWorld(x, y);
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
        try {
            window = init();
            if (!window) {
                throw std::runtime_error("Failed to initialize GLFW window");
            }
        } catch (std::exception& e) {
            throw std::runtime_error(__FUNCTION__": " + std::string(e.what()));
        }
    }

    App::~App() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void App::start() {
        try {
            mainLoop();
        } catch (std::exception& e) {
            throw std::runtime_error(__FUNCTION__": " + std::string(e.what()));
        }
    }

    Texture* App::addTexture(const std::filesystem::path &path) {
        std::unique_ptr<Texture> texture = std::make_unique<Texture>(path);
        Texture* texturePtr = texture.get();
        textures.push_back(std::move(texture));
        return texturePtr;
    }

    Rectangle* App::addRectangle(float width, float height) {
        std::unique_ptr<Rectangle> rect = std::make_unique<Rectangle>(width, height);
        Rectangle* rectPtr = rect.get();
        shapes.push_back(std::move(rect));
        return rectPtr;
    }
}
