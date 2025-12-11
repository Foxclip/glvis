#pragma once

#include "vector.h"
#include "shader.h"

namespace glvis {

    class Shape {
    public:
        float getX() const;
        float getY() const;
        Vector2 getPosition() const;
        float getRotation() const;
        const Vector2& getScale() const;
        const Vector2& getPivot() const;
        void setPosition(float x, float y);
        void setPosition(const Vector2& position);
        void setRotation(float rotation);
        void setScale(float x, float y);
        void setScale(const Vector2& scale);
        void setOrigin(float x, float y);
        void setOrigin(const Vector2& origin);
        void setShader(Shader* shader);
        virtual void render(const glm::mat4& view, const glm::mat4& projection) const = 0;

    protected:
        Shader* shader = nullptr;
        Vector2 position;
        float rotation = 0.0f;
        Vector2 scale = Vector2(1.0f, 1.0f);
        Vector2 origin = Vector2(0.0f, 0.0f);

    private:

    };

}
