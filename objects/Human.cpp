#include "Human.h"

Human::Human(glm::vec3 pos, glm::vec3 rot, int arm_seperation, int leg_seperation, TextureGroup *bodyTexture, TextureGroup *headTexture, Shader *shader) : Cylinder(0.5, 0.1)
{
    setShader(shader);
    setTextureGroup(bodyTexture);
    translate(pos);
    rotate(rot.z, glm::vec3(0, 0, 1));
    rotate(rot.y, glm::vec3(0, 1, 0));
    rotate(rot.x, glm::vec3(1, 0, 0));

    glm::vec3 armRotationAxis = glm::vec3(0, 0, 1);
    glm::vec3 legRotationAxis = glm::vec3(1, 0, 0);

    leftArm = new Cylinder(0.4, 0.05);
    leftArm->setInformation(bodyTexture, shader);
    leftArm->setModel(model);
    leftArm->translate(glm::vec3(0, 0.3, 0));
    leftArm->rotate(-90, armRotationAxis);

    rightArm = new Cylinder(0.4, 0.05);
    rightArm->setInformation(bodyTexture, shader);
    rightArm->setModel(model);
    rightArm->translate(glm::vec3(0, 0.3, 0));
    rightArm->rotate(90, armRotationAxis);

    hips = new Sphere(0.12, 10, 10);
    hips->setInformation(bodyTexture, shader);
    hips->setModel(model);
    hips->translate(glm::vec3(0, -0.05, 0));

    //legs
    leftLeg = new Cylinder(0.5, 0.05);
    leftLeg->setInformation(bodyTexture, shader);
    leftLeg->setModel(model);
    leftLeg->translate(glm::vec3(-0.05, -0.5, 0));
    leftLeg->rotate(leg_seperation, legRotationAxis);

    rightLeg = new Cylinder(0.5, 0.05);
    rightLeg->setInformation(bodyTexture, shader);
    rightLeg->setModel(model);
    rightLeg->translate(glm::vec3(0.05, -0.5, 0));

    //head
    head = new Sphere(0.15, 10, 10);
    head->setInformation(headTexture, shader);
    head->setModel(model);
    head->translate(glm::vec3(0, 0.6, 0));
}

void Human::draw()
{
    Cylinder::draw();
    leftArm->draw();
    rightArm->draw();
    hips->draw();
    leftLeg->draw();
    rightLeg->draw();
    head->draw();
}

void Human::update(glm::vec3 pos, glm::vec3 rot, int arm_seperation, int leg_seperation)
{

    this->arm_seperation = arm_seperation;
    this->leg_seperation = leg_seperation;
    translate(pos);
    rotate(rot.z, glm::vec3(0, 0, 1));
    rotate(rot.y, glm::vec3(0, 1, 0));
    rotate(rot.x, glm::vec3(1, 0, 0));

    leftArm->setModel(model);
    leftArm->translate(glm::vec3(0, 0.3, 0));
    leftArm->rotate(-arm_seperation, glm::vec3(0, 0, 1));

    rightArm->setModel(model);
    rightArm->translate(glm::vec3(0, 0.3, 0));
    rightArm->rotate(arm_seperation, glm::vec3(0, 0, 1));

    hips->setModel(model);
    hips->translate(glm::vec3(0, -0.05, 0));

    leftLeg->setModel(model);
    leftLeg->translate(glm::vec3(-0.05, -0.0, 0));
    leftLeg->rotate(leg_seperation, glm::vec3(1, 0, 0));

    rightLeg->setModel(model);
    rightLeg->translate(glm::vec3(0.05, -0.0, 0));
    rightLeg->rotate(-leg_seperation, glm::vec3(1, 0, 0));

    head->setModel(model);
    head->translate(glm::vec3(0, 0.6, 0));

}

void Human::set(glm::vec3 pos, glm::vec3 rot)
{
    resetModel();
    update(pos, rot, arm_seperation, leg_seperation);
}
