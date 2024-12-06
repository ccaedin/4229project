#include "Tree.h"


Tree::Tree(glm::vec3 pos, float len, float wid, TextureGroup *barkTexture, TextureGroup *leavesTexture, Shader *shader) : Cylinder(len, wid)
{
    this->barkTexture = barkTexture;
    this->leavesTexture = leavesTexture;
    this->shader = shader;
    setTextureGroup(barkTexture);
    translate(glm::vec3(0, -1, 0));
    translate(pos);

    leaves = new Sphere(wid * 4, 10, 10);
    leaves->setModel(getModel());
    leaves->setTextureGroup(leavesTexture);
    leaves->setShader(shader);
    leaves->translate(glm::vec3(0, len, 0));

}

void Tree::draw()
{
    Cylinder::draw();
    leaves->draw();
}
