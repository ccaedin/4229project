#ifndef SPHERE_H
#define SPHERE_H

#include "../lib.h"
#include "../Mesh.h"

class Sphere : public Mesh
{
public:
    Sphere(float radius);
    void draw() override;
    void computeTangentBasis(
        // inputs
        std::vector<glm::vec3> & vertices,
        std::vector<glm::vec2> & uvs,
        std::vector<glm::vec3> & normals,
        // outputs
        std::vector<glm::vec3> & tangents,
        std::vector<glm::vec3> & bitangents) override;

private:
    int numSideVertices;
    int numCapVertices;
    int numVertices;
};
#endif // CYLINDER_H