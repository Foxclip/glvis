#pragma once

#include "vector.h"

namespace glvis {

    class Shape {
    public:
        double getX() const;
        double getY() const;
        Vector2 getPosition() const;
        double getRotation() const;
        const Vector2& getScale() const;
        void setPosition(double x, double y);
        void setPosition(const Vector2& position);
        void setRotation(double rotation);
        void setScale(double x, double y);
        void setScale(const Vector2& scale);
        virtual void render() const = 0;

    protected:
        Vector2 position;
        double rotation = 0.0;
        Vector2 scale = Vector2(1.0, 1.0);

    private:

    };

}
