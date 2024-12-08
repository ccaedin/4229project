#ifndef HUMAN_H
#define HUMAN_H

#include "../lib.h"

#include "Cylinder.h"
#include "Sphere.h"

class Human : public Cylinder{
    public:
        Human(glm::vec3 pos, glm::vec3 rot, int arm_seperation, int leg_seperation, TextureGroup *bodyTexture, TextureGroup *headTexture, Shader *shader);
        void draw();

        void rotateArms(int angle);
        void rotateLegs(int angle);
        void update(glm::vec3 pos, glm::vec3 rot, int arm_seperation, int leg_seperation);
        void set(glm::vec3 pos, glm::vec3 rot);
    private:
        TextureGroup *bodyTexture;
        TextureGroup *headTexture;
        Shader *shader;
        Sphere *hips;
        Sphere *head;
        Cylinder *leftArm;
        Cylinder *rightArm;
        Cylinder *leftLeg;
        Cylinder *rightLeg;
        glm::vec3 pos;
        glm::vec3 rot;
        int arm_seperation;
        int leg_seperation;
};
#endif // HUMAN_H