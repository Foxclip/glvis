#pragma once

#include "vector.h"
#include "shape.h"

namespace glvis {

    class Rectangle : public Shape {
    public:
        Rectangle(double width, double height);
        double getWidth() const;
        double getHeight() const;
        Vector2 getSize() const;
        void render() const override;

    private:
        double width = 0.0;
        double height = 0.0;
        unsigned int VAO = 0;
        unsigned int VBO = 0;
        unsigned int EBO = 0;

    };

}
