#include <iostream>
#include "app.h"

int main() {

    try {
        glvis::App app;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    } catch (std::string& e) {
        std::cerr << e << std::endl;
    }

    
    return 0;
    
    // TODO: texture class
    // TODO: render textured rectangles
    // TODO: pivot point
    // TODO: Polygon shape
}
