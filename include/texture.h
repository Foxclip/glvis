#pragma once

#include <filesystem>

namespace glvis {

    class Texture {
    public:
        Texture(int width, int height);
        Texture(const std::filesystem::path& path);
        unsigned int getID() const;
        int getWidth() const;
        int getHeight() const;
        void bind();
        void unbind();
        
    private:
        unsigned int ID = 0;
        int width = 0;
        int height = 0;

    };

}
