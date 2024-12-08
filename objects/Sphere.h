#ifndef SPHERE_H
#define SPHERE_H

#include "../lib.h"
#include "../Mesh.h"

class Sphere : public Mesh
{
public:
    Sphere(float radius, int slicesVertical, int slicesHorizontal);
    void draw();
    void computeTangentBasis(
        // inputs
        std::vector<glm::vec3> & vertices,
        std::vector<glm::vec2> & uvs,
        std::vector<glm::vec3> & normals,
        // outputs
        std::vector<glm::vec3> & tangents,
        std::vector<glm::vec3> & bitangents);

private:

    std::vector<int> indices;
    GLuint indexBuffer;

    float radius;
    int numSlices;
    int numStacks;
    int numVertices;
    int numIndices;
    GLuint numPoleIndices;
    GLuint numSideIndices;

    GLuint northPoleOffset;
    GLuint sideOffset;
    GLuint southPoleOffset;
};
#endif // CYLINDER_H