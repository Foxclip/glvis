#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>
#include "rectangle.h"
#include "texture.h"
#include "render_texture.h"

namespace glvis {

    const int DEFAULT_WINDOW_WIDTH = 800;
    const int DEFAULT_WINDOW_HEIGHT = 600;
    const float CAMERA_ZOOM_FACTOR = 1.2f;

    class Camera {
    public:
        const glm::vec2& getPosition() const;
        float getZoom() const;
        void setPosition(const glm::vec2& pos);
        void setZoom(float zoom);

    private:
        glm::vec2 pos = glm::vec2(0.0f, 0.0f);
        float zoom = 1.0f;
    };

    class App {

    public:
        App();
        ~App();
        void start();
        Texture* addTexture(const std::filesystem::path& path);
        void removeTexture(Texture* texture);
        void removeTexture(const std::filesystem::path& path);
        Rectangle* addRectangle(float width, float height);

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
        std::unique_ptr<RenderTexture> screenTextureUptr = nullptr;
        std::map<std::string, std::unique_ptr<Texture>> textures;

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
        static void glad_pre_callback(const char* name, void* funcptr, int len_args, ...);
        static void glad_post_callback(const char* name, void* funcptr, int len_args, ...);
        void processWindowSize(int width, int height);
        void processMouse(double xpos, double ypos);
        void processMousePress(int button, int action, int mods);
        void processMouseScroll(double x, double y);
        void processMouseLeftPress(int x, int y);
        void processMouseRightPress(int x, int y);

    };

}
