#include <iostream>
#include "app.h"

int main() {

    try {

        glvis::App app;

        glvis::Texture* boxTexture = app.addTexture("box.jpg");
        glvis::Rectangle* rect1 = app.addRectangle(100.0f, 100.0f);
        rect1->setTexture(boxTexture);
        rect1->setPosition(0.0f, 0.0f);
        rect1->setRotation(glm::radians(45.0f));
        glvis::Rectangle* rect2 = app.addRectangle(100.0f, 100.0f);
        rect2->setTexture(boxTexture);
        rect2->setPosition(200.0f, 0.0f);
        rect2->setRotation(glm::radians(10.0f));

        app.start();

    } catch (const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
    } catch (std::string& e) {
        std::cerr << "ERROR: " << e << std::endl;
    }

    
    return 0;
    
    // TODO: render textured rectangles
    // TODO: resize textures
    // TODO: pivot point
    // TODO: Polygon shape
}
