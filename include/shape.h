#pragma once

#include "vector.h"

namespace glvis {

    class Shape {
    public:
        double getX() const;
        double getY() const;
        Vector2 getPosition() const;
        const Vector2& getScale() const;
        void setPosition(double x, double y);
        void setPosition(const Vector2& position);
        virtual void render() const = 0;

    private:
        double x = 0.0;
        double y = 0.0;
        Vector2 scale = Vector2(1.0, 1.0);

    };

}
