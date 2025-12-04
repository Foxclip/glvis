#pragma once

namespace glvis {

    class Texture {
    public:
        Texture(int width, int height);
        unsigned int getID() const;
        void bind();
        void unbind();
        
    private:
        unsigned int ID = 0;

    };

}
