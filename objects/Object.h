#ifndef OBJECT_H
#define OBJECT_H

#include "lib.h"

#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"
//dictionary
#include <map>

//the goal is to combine meshes, textures, and shaders into one object
class RenderUnit
{
    public:
        RenderUnit(Mesh *mesh, Texture *texture, Shader *shader);
        ~RenderUnit();
        void draw();
        glm::mat4 getModel();
    private:
        Mesh *mesh;
        Texture *texture;
        Shader *shader;
};

class Object
{
    public:
        void addRenderUnit(std::string name, Mesh *mesh, Texture *texture, Shader *shader);
    private:
        std::map<std::string, RenderUnit*> renderUnits;
};
    


#endif // OBJECT_H