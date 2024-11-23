#ifndef TEXTURE_H
#define TEXTURE_H

#include "lib.h"
#include <SDL2/SDL_image.h>

class Texture
{
    public:
        Texture(const std::string& filePath);
        ~Texture();

        void bind() const;
        void unbind() const;

    private:
        unsigned int textureID;
        std::string filePath;
    
        void loadTexture();
};
#endif // TEXTURE_H