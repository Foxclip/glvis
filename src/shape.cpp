#include "shape.h"

namespace glvis {

    float Shape::getX() const {
        return position.x;
    }

    float Shape::getY() const {
        return position.y;
    }

    Vector2 Shape::getPosition() const {
        return position;
    }

    float Shape::getRotation() const {
        return rotation;
    }

    const Vector2& Shape::getScale() const {
        return scale;
    }

    void Shape::setPosition(float x, float y) {
        this->position.x = x;
        this->position.y = y;
    }

    void Shape::setPosition(const Vector2& position) {
        this->position = position;
    }

    void Shape::setRotation(float rotation) {
        this->rotation = rotation;
    }

    void Shape::setScale(float x, float y) {
        this->scale.x = x;
        this->scale.y = y;
    }

    void Shape::setScale(const Vector2& scale) {
        this->scale = scale;
    }
}
