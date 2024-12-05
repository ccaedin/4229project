#include "Skybox.h"

Skybox::Skybox(Camera* camera) : Cube()
{
    this->camera = camera;
    Shader *shader = new Shader("./shaders/skybox.vert", "./shaders/skybox.frag");
    setShader(shader);
    // translate(camera->GetPosition());
    scale(glm::vec3(12, 12, 12));
    //the order is important and the photos are labels nx, px, py, ny, nz, pz
    std::vector<std::string> faces = {
        "./textures/skybox/px.png",
        "./textures/skybox/nx.png",
        "./textures/skybox/py.png",
        "./textures/skybox/ny.png",
        "./textures/skybox/pz.png",
        "./textures/skybox/nz.png",

    };
    cubemapTexture = loadCubemap(faces);
    
}

void Skybox::draw()
{
    glDepthFunc(GL_LEQUAL);
    // resetModel();
    // translate(camera->GetPosition());
    // scale(glm::vec3(20, 20, 20));
    setupDraw();
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);
    glDisableVertexAttribArray(4);
    glDepthFunc(GL_LESS);
}

void Skybox::setupDraw()
{
    shader->use();
    shader->setMat4("model", model);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
    shader->setInt("skybox", 0);


    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(
        0,                  // attribute
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glVertexAttribPointer(
        1,                  // attribute
        2,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );

    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glVertexAttribPointer(
        2,                  // attribute
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );

    glEnableVertexAttribArray(3);
    glBindBuffer(GL_ARRAY_BUFFER, tangentBuffer);
    glVertexAttribPointer(
        3,                  // attribute
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );

    glEnableVertexAttribArray(4);
    glBindBuffer(GL_ARRAY_BUFFER, bitangentBuffer);
    glVertexAttribPointer(
        4,                  // attribute
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );
}

unsigned int Skybox::loadCubemap(std::vector<std::string> faces)
{
        unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        SDL_Surface* surface = IMG_Load(faces[i].c_str());
        if (surface)
        {
            GLenum format;
            if (surface->format->BytesPerPixel == 4) { // 32-bit
                if (surface->format->Rmask == 0x000000ff)
                    format = GL_RGBA;
                else
                    format = GL_BGRA;
            } else if (surface->format->BytesPerPixel == 3) { // 24-bit
                if (surface->format->Rmask == 0x000000ff)
                    format = GL_RGB;
                else
                    format = GL_BGR;
            } else {
                SDL_Log("Image is not true color: %s", faces[i].c_str());
                SDL_FreeSurface(surface);
                return 0;
            }
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
                         0, format, surface->w, surface->h, 0, format, GL_UNSIGNED_BYTE, surface->pixels
            );
        }
        else
        {
            std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
        }
        SDL_FreeSurface(surface);           
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}
