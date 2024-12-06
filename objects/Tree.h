#include "../lib.h"
#include "Cylinder.h"
#include "Sphere.h"

class Tree : public Cylinder
{
    public:
        Tree(glm::vec3 pos, float len, float wid, TextureGroup* barkTexture, TextureGroup* leavesTexture, Shader* shader);
        void draw() override;
    private:
        TextureGroup* barkTexture;
        TextureGroup* leavesTexture;
        Sphere* leaves;
};