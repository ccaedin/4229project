#ifndef MESH_H
#define MESH_H

#include "lib.h"
#include "Texture.h" // Ensure that Texture.h is correctly included
#include "Shader.h"
class Mesh {
    public:
        Mesh(std::string path);
        Mesh(std::vector<glm::vec3> vertices, std::vector<glm::vec2> uvs, std::vector<glm::vec3> normals);
        Mesh(std::vector<glm::vec3> vertices, std::vector<glm::vec2> uvs, std::vector<glm::vec3> normals, std::vector<GLubyte> indices);
        Mesh(std::vector<glm::vec3> vertices, std::vector<glm::vec2> uvs, std::vector<glm::vec3> normals, std::vector<glm::vec3> tangents, std::vector<glm::vec3> bitangents, std::vector<GLubyte> indices);
        Mesh();
        ~Mesh();
        void draw();
        void draw_indexed();
        //transformations
        void translate(glm::vec3 translation) { model = glm::translate(model, translation); }
        void rotate(float angle, glm::vec3 axis) { model = glm::rotate(model, glm::radians(angle), axis); }
        void rotate(glm::vec3 angles) { model = glm::rotate(model, glm::radians(angles.z), glm::vec3(0, 0, 1)); model = glm::rotate(model, glm::radians(angles.y), glm::vec3(0, 1, 0)); model = glm::rotate(model, glm::radians(angles.x), glm::vec3(1, 0, 0));}
        void scale(glm::vec3 scale) { model = glm::scale(model, scale); }
        void resetModel() { model = glm::mat4(1.0f); }
        glm::mat4 getModel() { return model; }

        void setTextureGroup(TextureGroup *textureGroup);
        void setColorTexture(Texture *texture) { colorTexture = texture; }
        void setNormalTexture(Texture *texture) { normalTexture = texture; }
        void setModel(glm::mat4 model) { this->model = model; }

        void setInformation(TextureGroup *textureGroup, Shader *shader) { setTextureGroup(textureGroup); setShader(shader); }

        void setShader(Shader *shader) { this->shader = shader; }
        Shader* getShader() { return shader; }
    protected:
        bool loadOBJ(
            const char * path, 
            std::vector<glm::vec3> & out_vertices, 
            std::vector<glm::vec2> & out_uvs,
            std::vector<glm::vec3> & out_normals);
        void computeTangentBasis(
            // inputs
            std::vector<glm::vec3> & vertices,
            std::vector<glm::vec2> & uvs,
            std::vector<glm::vec3> & normals,
            // outputs
            std::vector<glm::vec3> & tangents,
            std::vector<glm::vec3> & bitangents);
        GLuint VAO, vertexBuffer, normalBuffer, uvBuffer, tangentBuffer, bitangentBuffer, elementBuffer;
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec2> uvs;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec3> tangents;
        std::vector<glm::vec3> bitangents;
        std::vector<GLubyte> indices;
        glm::mat4 model;
        Texture *colorTexture;
        Texture *normalTexture;
        Shader *shader;
        void loadMesh(std::string path);
        void setupMesh(std::vector<glm::vec3> vertices, std::vector<glm::vec2> uvs, std::vector<glm::vec3> normals);
        void setupMesh(std::vector<glm::vec3> vertices, std::vector<glm::vec2> uvs, std::vector<glm::vec3> normals, std::vector<glm::vec3> tangents, std::vector<glm::vec3> bitangents, std::vector<GLubyte> indices);
        void setupDraw();
};
#endif // MESH_H