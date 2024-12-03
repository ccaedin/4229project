#ifndef SHAPES_H
#define SHAPES_H

#pragma once
#include "lib.h"
#include "Texture.h"
#include "Mesh.h"
#include "objects/Cylinder.h"
#include "objects/Sphere.h"
#include "Shader.h"


void Vertex(double th, double ph);
Mesh* cylinder(float len, float wid, Texture *texure, Shader* shader);
Mesh* sphere(glm::vec3 pos, float r, Texture *texture);
Mesh* tree(glm::vec3 pos, glm::vec3 rot, Texture *bark, Texture *leaves);
Mesh* human(glm::vec3 pos, glm::vec3 rot, int arm_seperation, int leg_seperation, Texture *body_texture, Texture *head_texture);
Mesh* cube(glm::vec3 pos, glm::vec3 rot, Texture *texture[], float reps, Shader* shader);
std::vector<Mesh*> house(glm::vec3 pos, glm::vec3 rot,  Texture* house_text[], float house_reps, Texture* roof_text[], Shader* shader);
Mesh* sun(glm::vec3 pos, glm::vec3 rot, float shiny, int emission, Texture *texture);
Mesh* moon(glm::vec3 pos, glm::vec3 rot, float shiny, int emission, Texture *texture);

#endif // SHAPES_H
