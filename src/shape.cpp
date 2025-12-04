#include "shape.h"

namespace glvis {

    double Shape::getX() const {
        return x;
    }

    double Shape::getY() const {
        return y;
    }

    Vector2 Shape::getPosition() const {
        return Vector2(x, y);
    }

}
