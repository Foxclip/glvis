#include <iostream>
#include "app.h"

int main() {

    try {
        App app;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    } catch (std::string& e) {
        std::cerr << e << std::endl;
    }

    return 0;
}
