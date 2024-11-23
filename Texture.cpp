#include "Texture.h"

Texture::Texture(const std::string& filePath)
    : textureID(0), filePath(filePath)
{
    loadTexture();
}

Texture::~Texture()
{
    glDeleteTextures(1, &textureID);
}

void Texture::bind() const
{
    glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::loadTexture()
{
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (surface == nullptr) {
        SDL_Log("Unable to load image: %s", IMG_GetError());
        return;
    }

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    GLenum format;
    if (surface->format->BytesPerPixel == 4) { // 32-bit
        if (surface->format->Rmask == 0x000000ff)
            format = GL_RGBA;
        else
            format = GL_BGRA;
    } else if (surface->format->BytesPerPixel == 3) { // 24-bit
        if (surface->format->Rmask == 0x000000ff)
            format = GL_RGB;
        else
            format = GL_BGR;
    } else {
        SDL_Log("Image is not true color: %s", filePath.c_str());
        SDL_FreeSurface(surface);
        return;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, format, surface->w, surface->h, 0, format, GL_UNSIGNED_BYTE, surface->pixels);
    if (glGetError()) {
        printf("Error loading texture %s \n", filePath.c_str());
    }
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    SDL_FreeSurface(surface);
}