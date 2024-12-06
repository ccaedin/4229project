#ifndef TEXTURE_H
#define TEXTURE_H

#include "lib.h"
#include <SDL2/SDL_image.h>
#include <map>


class Texture
{
    public:
        Texture(const std::string& filePath);
        ~Texture();

        void bind() const;
        void unbind() const;

        unsigned int getID() { return textureID; }

    private:
        unsigned int textureID;
        std::string filePath;
    
        void loadTexture();
};

enum TextureType
{
    DIFFUSE,
    SPECULAR,
    NORMAL
};

class TextureGroup
{
    public:
        TextureGroup(std::vector<std::string> filePaths);
        TextureGroup(Texture *diffuse, Texture *specular, Texture *normal);
        TextureGroup(Texture *diffuse, Texture *normal);
        ~TextureGroup();

        void bind(TextureType type) const;
        void unbind() const;
        Texture* getTexture(TextureType type) { return textureMap.at(type); }

    private:
        std::map<TextureType, Texture*> textureMap;
        void loadTextures();
};

#endif // TEXTURE_H