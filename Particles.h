#ifndef PARTICLES_H
#define PARTICLES_H

#include "lib.h"
#include "Shader.h"
#include "Camera.h"
#include <algorithm>

// static const std::vector<glm::vec3> PARTICLE_VERTEX_DATA = { 
//     glm::vec3(-0.5f, -0.5f, 0.0f),
//     glm::vec3(0.5f, -0.5f, 0.0f),
//     glm::vec3(-0.5f, 0.5f, 0.0f),
//     glm::vec3(0.5f, 0.5f, 0.0f),
// };
const std::vector<glm::vec3> PARTICLE_VERTEX_DATA = {
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
constexpr int MAX_PARTICLES = 50;
struct Particle {
    glm::vec3 pos, speed;
    float size, angle;
    float life;
    float cameraDistance;
    bool operator<(const Particle& that) const {
        return this->cameraDistance > that.cameraDistance;
    }
};

class Particles
{
    public:
        Particles(glm::vec3 origin, Camera* camera, Shader* shader);
        void draw(float deltaTime);
    private:
        glm::vec3 origin;
        int lastUsedParticle = 0;
        int findDeadParticle();
        std::vector<Particle> particles;
        GLuint VAO;
        GLuint particles_vertex_buffer;
        GLuint particles_position_buffer;
        GLuint particles_size_buffer;
        std::vector<glm::vec3> position_data;
        std::vector<GLuint> size_data;


        Shader* shader;
        Camera* camera;
};

#endif // PARTICLES_H