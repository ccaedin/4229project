#include "Particles.h"

Particles::Particles(glm::vec3 origin, Camera* camera, Shader* shader)
{
    this->shader = shader;
    this->origin = origin;
    this->camera = camera;

    this->particles = std::vector<Particle>(MAX_PARTICLES);
    this->position_data = std::vector<glm::vec3>(MAX_PARTICLES);
    this->size_data = std::vector<GLuint>(MAX_PARTICLES);

    for(int i = 0; i < MAX_PARTICLES; i++)
    {
        particles[i].life = -1.0f;
        particles[i].cameraDistance = -1.0f;
    }
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &particles_vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, particles_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*PARTICLE_VERTEX_DATA.size(), &PARTICLE_VERTEX_DATA[0], GL_STATIC_DRAW);

    glGenBuffers(1, &particles_position_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*particles.size(), NULL, GL_STREAM_DRAW);
}

void Particles::draw(float deltaTime)
{
    //find out how many new particles we need to create
    int newParticles = (int)(deltaTime * 1000.0);
    if(newParticles > (int)(0.016f * 1000.0))
        newParticles = (int)(0.016f * 1000.0); //limit to 60 fps
    
    for(int i = 0; i < newParticles; i++) {
        int particleIndex = findDeadParticle();
        particles[particleIndex].life = 5.0;
        particles[particleIndex].pos = origin;
        particles[particleIndex].cameraDistance = glm::length(particles[particleIndex].pos - camera->GetPosition());

        float spread = 0.5f;
        glm::vec3 maindir = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 randomdir = glm::vec3(
            (rand()%2000 - 1000.0f)/1000.0f,
            (rand()%2000 - 1000.0f)/1000.0f,
            (rand()%2000 - 1000.0f)/1000.0f
        );

        particles[particleIndex].speed = maindir + randomdir*spread;

        particles[particleIndex].size = (rand()%1000)/3000.0f + 0.1f;
    }

    //simulate

    int numParticles = 0;
    for(int i = 0; i<MAX_PARTICLES; i++)
    {
        Particle& p = particles[i];
        p.life -= deltaTime;
        if(p.life > 0.0f)
        {
            // p.speed += glm::vec3(0.0f, -9.81f, 0.0f) * (float)deltaTime * 0.5f;
            p.pos += p.speed * (float)(deltaTime/10.0);
            p.cameraDistance = glm::length(p.pos - camera->GetPosition());

            position_data[numParticles] = p.pos;

            size_data[numParticles] = p.size;

            numParticles++;
        }
    }

    //maybe sort the particles
    std::sort(particles.begin(), particles.end());
    //bin&
    glBindVertexArray(VAO);
    //fill the gpu buffers
    glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
    //make sure only fill the data that we are using
    glBufferData(GL_ARRAY_BUFFER, numParticles * sizeof(glm::vec3), &position_data[0], GL_STREAM_DRAW);

    // glBindBuffer(GL_ARRAY_BUFFER, particles_size_buffer);
    // glBufferData(GL_ARRAY_BUFFER, numParticles * sizeof(GLuint), &size_data[0], GL_STREAM_DRAW);

    //draw the particles
    shader->use();
    shader->setMat4("view", camera->GetViewMatrix());
    shader->setMat4("projection", camera->GetProjectionMatrix());

    shader->setVec3("color", glm::vec3(1, 0.1, 0));
    shader->setVec3("offset", glm::vec3(0, 0, 0));

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, particles_vertex_buffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glVertexAttribDivisor(0, 0); //does not move between instances
    glVertexAttribDivisor(1, 1); //move between instances

    glDrawArraysInstanced(GL_TRIANGLES, 0, PARTICLE_VERTEX_DATA.size(), numParticles);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    glBindVertexArray(0);
}

int Particles::findDeadParticle()
{
    	for(int i=lastUsedParticle; i<MAX_PARTICLES; i++){
		if (particles[i].life < 0){
			lastUsedParticle = i;
			return i;
		}
	}
    //search from the beginning if nothing was found from the last used particle
	for(int i=0; i<lastUsedParticle; i++){
		if (particles[i].life < 0){
			lastUsedParticle = i;
			return i;
		}
	}

	return 0; // All particles are taken, override the first one
}