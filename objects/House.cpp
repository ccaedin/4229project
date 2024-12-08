#include "House.h"

House::House(glm::vec3 pos, glm::vec3 scale, glm::vec3 rot, TextureGroup *brickTexture, TextureGroup *roofTexture, TextureGroup *torchTexture, TextureGroup *fireTexture, Shader *shader) : Cube()
{
    // loadOBJ("cube.obj", vertices, uvs, normals);
    // setupMesh(vertices, uvs, normals);
    this->shader = shader;

    setTextureGroup(brickTexture);   


    translate(pos);
    rotate(rot.z, glm::vec3(0, 0, 1));
    rotate(rot.y, glm::vec3(0, 1, 0));
    rotate(rot.x, glm::vec3(1, 0, 0));


    House::scale(scale);

    std::vector<glm::vec3> roof_vertices = {
        glm::vec3(1, -0, -1),
        glm::vec3(-1, -0, -1),
        glm::vec3(0, 1, 0),
        glm::vec3(-1, -0, 1),
        glm::vec3(1, -0, 1),
        glm::vec3(0, 1, 0),
        glm::vec3(-1, -0, -1),
        glm::vec3(-1, -0, 1),
        glm::vec3(0, 1, 0),
        glm::vec3(1, -0, 1),
        glm::vec3(1, -0, -1),
        glm::vec3(0, 1, 0),
    };
    //uv
    std::vector<glm::vec2> roof_uvs = {
        glm::vec2(0, 0),
        glm::vec2(1, 0),
        glm::vec2(0.5, 1),
        glm::vec2(0, 0),
        glm::vec2(1, 0),
        glm::vec2(0.5, 1),
        glm::vec2(0, 0),
        glm::vec2(1, 0),
        glm::vec2(0.5, 1),
        glm::vec2(0, 0),
        glm::vec2(1, 0),
        glm::vec2(0.5, 1),
    };
    std::vector<glm::vec3> roof_normals = {
        glm::vec3(-0, 0.7071, -0.7071),
        glm::vec3(-0, 0.7071, -0.7071),
        glm::vec3(-0, 0.7071, -0.7071),
        glm::vec3(-0, 0.7071, 0.7071),
        glm::vec3(-0, 0.7071, 0.7071),
        glm::vec3(-0, 0.7071, 0.7071),
        glm::vec3(-0.7071, 0.7071, -0),
        glm::vec3(-0.7071, 0.7071, -0),
        glm::vec3(-0.7071, 0.7071, -0),
        glm::vec3(0.7071, 0.7071, -0),
        glm::vec3(0.7071, 0.7071, -0),
        glm::vec3(0.7071, 0.7071, -0),
    };

    roof = new Mesh(roof_vertices, roof_uvs, roof_normals);

    roof->setModel(model);
    roof->translate(glm::vec3(0, 0.9, 0));
    roof->rotate(rot.y, glm::vec3(0, 1, 0));
    roof->rotate(rot.x, glm::vec3(1, 0, 0));
    roof->scale(glm::vec3(1.2, 1.2, 1.2));
    


    roof->setShader(shader);
    roof->setTextureGroup(roofTexture);



    //for now
    fireTexture = torchTexture;
    float torchLength = 0.5;
    int torchAngle = -35;
    float torchPos = 0.7;
    float torchHeight = 0.4;
    float torchBallRadius = 0.1;
    torch1 = new Cylinder(torchLength, 0.03);
    
    torch1->setTextureGroup(torchTexture);
    torch1->setShader(shader);

    torch1->setModel(model);
    torch1->translate(glm::vec3(1, torchHeight, -torchPos));
    torch1->rotate(torchAngle, glm::vec3(0, 0, 1));

    //torch ball 1
    torch1Fire = new Sphere(torchBallRadius, 10, 10);
    torch1Fire->setModel(torch1->getModel());
    //based on the angle of the torch and the length, but the ball at the end of the torch
    torch1Fire->translate(glm::vec3(0, torchLength, 0));

    torch1Fire->setTextureGroup(torchTexture);
    torch1Fire->setShader(shader);

    glm::vec3 torch1FirePos = glm::vec3(torch1Fire->getModel() * glm::vec4(1, 1, 1, 1));
    lightPositions.push_back(torch1FirePos);


    torch2 = new Cylinder(torchLength, 0.03);
    
    torch2->setTextureGroup(torchTexture);
    torch2->setShader(shader);

    torch2->setModel(model);
    torch2->translate(glm::vec3(1, torchHeight, torchPos));
    torch2->rotate(torchAngle, glm::vec3(0, 0, 1));

    //torch ball 2
    torch2Fire = new Sphere(torchBallRadius, 10, 10);
    torch2Fire->setTextureGroup(fireTexture);
    torch2Fire->setShader(shader);


    torch2Fire->setModel(torch2->getModel());
    //based on the angle of the torch and the length, but the ball at the end of the torch
    torch2Fire->translate(glm::vec3(0, torchLength, 0));
    //geth the position of the torch from the model matrix
    glm::vec3 torch2FirePos = glm::vec3(torch2Fire->getModel() * glm::vec4(1, 1, 1, 1));
    lightPositions.push_back(torch2FirePos);
}

void House::draw()
{
    Cube::draw();
    roof->draw();
    torch1->draw();
    torch1Fire->draw();
    torch2->draw();
    torch2Fire->draw();

}