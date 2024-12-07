#ifndef HOUSE_H
#define HOUSE_H

#include "../lib.h"
#include "../Mesh.h"
#include "Cube.h"
#include "Cylinder.h"
#include "Sphere.h"
#include "../Mesh.h"

class House : public Cube
{
public:
    House(glm::vec3 pos, glm::vec3 scale, glm::vec3 rot, TextureGroup* brickTexture, TextureGroup* roofTexture, TextureGroup *torchTexture, TextureGroup* fireTexture, Shader* shader);
    void draw();
    std::vector<glm::vec3> getLights() { return lightPositions; }

private:

    Texture *brickColor;
    Texture *brickNormal;

    Texture *roofColor;
    Texture *roofNormal;

    Texture* torchColor;
    Texture* torchNormal;

    Cylinder* torch1;
    Sphere* torch1Fire;
    
    Cylinder* torch2;
    Sphere* torch2Fire;

    Mesh* roof;

    std::vector<glm::vec3> lightPositions;

};
#endif // HOUSE_H