#ifndef CUBE_H
#define CUBE_H

#include "../lib.h"
#include "../Mesh.h"

class Cube: public Mesh
{
    public:
        Cube();
    protected:
        const std::vector<glm::vec3> VERTICES = {
        glm::vec3(-1, -1, 1),
        glm::vec3(-1, 1, -1),
        glm::vec3(-1, -1, -1),
        glm::vec3(-1, 1, 1),
        glm::vec3(1, 1, -1),
        glm::vec3(-1, 1, -1),
        glm::vec3(1, 1, 1),
        glm::vec3(1, -1, -1),
        glm::vec3(1, 1, -1),
        glm::vec3(1, -1, 1),
        glm::vec3(-1, -1, -1),
        glm::vec3(1, -1, -1),
        glm::vec3(1, 1, -1),
        glm::vec3(-1, -1, -1),
        glm::vec3(-1, 1, -1),
        glm::vec3(-1, 1, 1),
        glm::vec3(1, -1, 1),
        glm::vec3(1, 1, 1),
        glm::vec3(-1, -1, 1),
        glm::vec3(-1, 1, 1),
        glm::vec3(-1, 1, -1),
        glm::vec3(-1, 1, 1),
        glm::vec3(1, 1, 1),
        glm::vec3(1, 1, -1),
        glm::vec3(1, 1, 1),
        glm::vec3(1, -1, 1),
        glm::vec3(1, -1, -1),
        glm::vec3(1, -1, 1),
        glm::vec3(-1, -1, 1),
        glm::vec3(-1, -1, -1),
        glm::vec3(1, 1, -1),
        glm::vec3(1, -1, -1),
        glm::vec3(-1, -1, -1),
        glm::vec3(-1, 1, 1),
        glm::vec3(-1, -1, 1),
        glm::vec3(1, -1, 1),
    };
    const float repX = 1;
    const float repY = 1;
    const std::vector<glm::vec2> UVS = {
        glm::vec2(repX, 0),
        glm::vec2(0, repY),
        glm::vec2(0, 0),
        glm::vec2(repX, 0),
        glm::vec2(0, repY),
        glm::vec2(0, 0),
        glm::vec2(repX, 0),
        glm::vec2(0, repY),
        glm::vec2(0, 0),
        glm::vec2(repX, 0),
        glm::vec2(0, repY),
        glm::vec2(0, 0),
        glm::vec2(repX, 0),
        glm::vec2(0, repY),
        glm::vec2(0, 0),
        glm::vec2(repX, 0),
        glm::vec2(0, repY),
        glm::vec2(0, 0),
        glm::vec2(repX, 0),
        glm::vec2(repX, repY),
        glm::vec2(0, repY),
        glm::vec2(repX, 0),
        glm::vec2(repX, repY),
        glm::vec2(0, repY),
        glm::vec2(repX, 0),
        glm::vec2(repX, repY),
        glm::vec2(0, repY),
        glm::vec2(repX, 0),
        glm::vec2(repX, repY),
        glm::vec2(0, repY),
        glm::vec2(repX, 0),
        glm::vec2(repX, repY),
        glm::vec2(0, repY),
        glm::vec2(repX, 0),
        glm::vec2(repX, repY),
        glm::vec2(0, repY)
    };
    const std::vector<glm::vec3> NORMALS = {
        glm::vec3(-1, -0, -0),
        glm::vec3(-1, -0, -0),
        glm::vec3(-1, -0, -0),

        glm::vec3(-0, 1, -0),
        glm::vec3(-0, 1, -0),
        glm::vec3(-0, 1, -0),
        glm::vec3(1, -0, -0),
        glm::vec3(1, -0, -0),
        glm::vec3(1, -0, -0),
        
        glm::vec3(-0, -1, -0),
        glm::vec3(-0, -1, -0),
        glm::vec3(-0, -1, -0),

        glm::vec3(-0, -0, -1),
        glm::vec3(-0, -0, -1),
        glm::vec3(-0, -0, -1),
        
        glm::vec3(-0, -0, 1),
        glm::vec3(-0, -0, 1),
        glm::vec3(-0, -0, 1),

        glm::vec3(-1, -0, -0),
        glm::vec3(-1, -0, -0),
        glm::vec3(-1, -0, -0),

        glm::vec3(-0, 1, -0),
        glm::vec3(-0, 1, -0),
        glm::vec3(-0, 1, -0),

        glm::vec3(1, -0, -0),
        glm::vec3(1, -0, -0),
        glm::vec3(1, -0, -0),

        glm::vec3(-0, -1, -0),
        glm::vec3(-0, -1, -0),
        glm::vec3(-0, -1, -0),

        glm::vec3(-0, -0, -1),
        glm::vec3(-0, -0, -1),
        glm::vec3(-0, -0, -1),

        glm::vec3(-0, -0, 1),
        glm::vec3(-0, -0, 1),
        glm::vec3(-0, -0, 1),
    };
};
#endif // CUBE_H