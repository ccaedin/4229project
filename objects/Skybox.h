#include "Cube.h"
#include "../Camera.h"

class Skybox : public Cube
{
    public:
        Skybox(Camera *camera);
        void draw();
    private:
        void setupDraw();
        Camera *camera;
        unsigned int loadCubemap(std::vector<std::string> faces);
        unsigned int cubemapTexture;
};
