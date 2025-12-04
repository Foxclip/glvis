#pragma once

#include "vector.h"

namespace glvis {

    class Shape {
    public:
        double getX() const;
        double getY() const;
        Vector2 getPosition() const;
        virtual void render() const = 0;

    private:
        double x = 0.0;
        double y = 0.0;

    };

}
