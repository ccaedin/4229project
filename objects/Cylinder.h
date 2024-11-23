#ifndef CYLINDER_H
#define CYLINDER_H

#include "../lib.h"
#include "../Mesh.h"

class Cylinder : public Mesh
{
public:
    Cylinder(float len, float wid);
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