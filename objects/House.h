#ifndef HOUSE_H
#define HOUSE_H

#include "../lib.h"
#include "../Mesh.h"
#include "Cube.h"
#include "Cylinder.h"
#include "Sphere.h"
#include "../Mesh.h"
#include "../Particles.h"

class House : public Cube
{
public:
    House(glm::vec3 pos, glm::vec3 scale, glm::vec3 rot, TextureGroup* brickTexture, TextureGroup* roofTexture, TextureGroup *torchTexture, TextureGroup* fireTexture, Shader* shader, Shader* smokeShader, Camera* camera);
    void draw(float deltaTime);
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
    Particles* torch1Smoke;
    
    Cylinder* torch2;
    Sphere* torch2Fire;
    Particles* torch2Smoke;

    Mesh* roof;

    std::vector<glm::vec3> lightPositions;

    Camera* camera;

};
#endif // HOUSE_H