#pragma once

#include "vector.h"

namespace glvis {

    class Shape {
    public:
        float getX() const;
        float getY() const;
        Vector2 getPosition() const;
        float getRotation() const;
        const Vector2& getScale() const;
        void setPosition(float x, float y);
        void setPosition(const Vector2& position);
        void setRotation(float rotation);
        void setScale(float x, float y);
        void setScale(const Vector2& scale);
        virtual void render() const = 0;

    protected:
        Vector2 position;
        float rotation = 0.0f;
        Vector2 scale = Vector2(1.0f, 1.0f);

    private:

    };

}
