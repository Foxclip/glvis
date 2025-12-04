#include "shape.h"

namespace glvis {

    double Shape::getX() const {
        return position.x;
    }

    double Shape::getY() const {
        return position.y;
    }

    Vector2 Shape::getPosition() const {
        return position;
    }

    double Shape::getRotation() const {
        return rotation;
    }

    const Vector2& Shape::getScale() const {
        return scale;
    }

    void Shape::setPosition(double x, double y) {
        this->position.x = x;
        this->position.y = y;
    }

    void Shape::setPosition(const Vector2& position) {
        this->position = position;
    }

    void Shape::setRotation(double rotation) {
        this->rotation = rotation;
    }

    void Shape::setScale(double x, double y) {
        this->scale.x = x;
        this->scale.y = y;
    }

    void Shape::setScale(const Vector2& scale) {
        this->scale = scale;
    }
}
