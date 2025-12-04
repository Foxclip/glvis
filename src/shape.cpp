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

    const Vector2& Shape::getScale() const {
        return scale;
    }

    void Shape::setPosition(double x, double y) {
        this->x = x;
        this->y = y;
    }

    void Shape::setPosition(const Vector2& position) {
        this->x = position.x;
        this->y = position.y;
    }

}
