#include "shapes.h"

static glm::vec3 zero = glm::vec3(0, 0, 0);

void Vertex(double th, double ph)
{
    //    glColor3f(Cos(th)*Cos(th) , Sin(ph)*Sin(ph) , Sin(th)*Sin(th));
    double x = Sin(th) * Cos(ph);
    double y = Sin(ph);
    double z = Cos(th) * Cos(ph);
    glNormal3d(x,y,z);
    glVertex3d(x, y, z);
}

Mesh* cylinder(float len, float wid, Texture *texure, Shader* shader)
{
    Cylinder *cylinder = new Cylinder(len, wid);
    cylinder->setShader(shader);
    cylinder->setColorTexture(texure);
    cylinder->setNormalTexture(texure);

    return cylinder;
}
int inc = 10;
Mesh* sphere(glm::vec3 pos, float r, Texture *texture)
{
    glPushMatrix();
    //  Offset
    glTranslated(pos.x, pos.y, pos.z);
    glScaled(r, r, r);
    //  Latitude bands
    if(texture)
        texture->bind();
    for (int ph = -90; ph < 90; ph += inc)
    {
        glBegin(GL_QUAD_STRIP);
        for (int th = 0; th <= 360; th += 2*inc)
        {
            float texX = (float)th / 360.0f;
            float texY1 = (float)(ph + 90) / 180.0f;
            float texY2 = (float)(ph + inc + 90) / 180.0f;

            glTexCoord2f(texX, texY1);
            Vertex(th, ph);
            glTexCoord2f(texX, texY2);
            Vertex(th, ph + inc);
        }
        glEnd();
    }
    if(texture) texture->unbind();
    glPopMatrix();
}

Mesh* tree(glm::vec3 pos, glm::vec3 rot, Texture *bark, Texture *leaves)
{
    // glPushMatrix();
    // //  Offset
    // glTranslated(pos.x, pos.y, pos.z);
    // glRotated(rot.x, 1, 0, 0);
    // glRotated(rot.y, 0, 1, 0);
    // glRotated(rot.z, 0, 0, 1);
    // // draw trunk brown
    // // glColor3f(0.36, 0.20, 0.09);
    // glColor3f(1,1,1);
    // glMaterialfv(GL_FRONT, GL_SPECULAR, glm::value_ptr(glm::vec4(0.36, 0.20, 0.09, 1)));
    // glMaterialfv(GL_FRONT, GL_EMISSION, glm::value_ptr(glm::vec4(0, 0, 0, 1)));

    // cylinder(zero, 1, 0.1, zero, bark , true);
    // // draw leaves
    // // dark green
    // glColor3f(0, 0.5, 0);
    // //light green specular
    // // GLfloat mat_specular[] = {0, 1, 0, 1.0};
    // // glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    // glRotated(90, 0, 0, 1);
    // sphere(zero, 0.3, leaves);
    // glPopMatrix();
}

Mesh* human(glm::vec3 pos, glm::vec3 rot, int arm_seperation, int leg_seperation, Texture *body_texture, Texture *head_texture)
{
    // glPushMatrix();
    // //  Offset
    // glTranslated(pos.x, pos.y, pos.z);
    // glRotated(rot.x, 1, 0, 0);
    // glRotated(rot.y, 0, 1, 0);
    // glRotated(rot.z, 0, 0, 1);

    // glColor3f(1,1,1);
    // glColor3f(1,1, 1);
    // cylinder(zero, 0.5, 0.1, zero, body_texture, true);
    // // offset and rotate
    // // arms
    // // skins color

    // cylinder(glm::vec3(0.3, 0, 0), 0.4, 0.05, glm::vec3(0,arm_seperation, 0 ), body_texture, true);
    // cylinder(glm::vec3(0.3, 0, 0), 0.4, 0.05, glm::vec3(0, -arm_seperation, 0), body_texture, true);



    // // hips
    // sphere(zero, 0.12, body_texture);
    // // legs 45 degrees out
    // // dark cacky color
    // glColor3f(0.36, 0.20, 0.09);
    // cylinder(glm::vec3(0, 0, -0.05), 0.5, 0.05, glm::vec3(0, 0, leg_seperation), body_texture, true);
    // cylinder(glm::vec3(0, 0, 0.05), 0.5, 0.05, glm::vec3(0, 0, -leg_seperation), body_texture, true);

    // // ankles, at the end of the legs leg_seperation out

    // glDisable(GL_TEXTURE_2D);
    // //skin color
    // glColor3f(1, 0.8, 0.6);
    // sphere(glm::vec3(0.6, 0, 0), 0.15, head_texture);
    // glEnable(GL_TEXTURE_2D);
    // glPopMatrix();
}

Mesh* cube(glm::vec3 pos, glm::vec3 rot, Texture **texture, float rep, Shader* shader)
{
    std::vector<glm::vec3> vertices = {
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
    float repX = rep;
    float repY = rep;
    std::vector<glm::vec2> uvs = {
        glm::vec2(repX, 0),
        glm::vec2(0, repY),
        glm::vec2(0, 0),
        glm::vec2(repX, 0),
        glm::vec2(0, repY),
        glm::vec2(0, 0),
        glm::vec2(repX, 0),
        glm::vec2(0, repY),
        glm::vec2(0, 0),
        glm::vec2(repX, 0),
        glm::vec2(0, repY),
        glm::vec2(0, 0),
        glm::vec2(repX, 0),
        glm::vec2(0, repY),
        glm::vec2(0, 0),
        glm::vec2(repX, 0),
        glm::vec2(0, repY),
        glm::vec2(0, 0),
        glm::vec2(repX, 0),
        glm::vec2(repX, repY),
        glm::vec2(0, repY),
        glm::vec2(repX, 0),
        glm::vec2(repX, repY),
        glm::vec2(0, repY),
        glm::vec2(repX, 0),
        glm::vec2(repX, repY),
        glm::vec2(0, repY),
        glm::vec2(repX, 0),
        glm::vec2(repX, repY),
        glm::vec2(0, repY),
        glm::vec2(repX, 0),
        glm::vec2(repX, repY),
        glm::vec2(0, repY),
        glm::vec2(repX, 0),
        glm::vec2(repX, repY),
        glm::vec2(0, repY)
    };
    std::vector<glm::vec3> normals = {
        glm::vec3(-1, -0, -0),
        glm::vec3(-1, -0, -0),
        glm::vec3(-1, -0, -0),
        glm::vec3(-0, 1, -0),
        glm::vec3(-0, 1, -0),
        glm::vec3(-0, 1, -0),
        glm::vec3(1, -0, -0),
        glm::vec3(1, -0, -0),
        glm::vec3(1, -0, -0),
        glm::vec3(-0, -1, -0),
        glm::vec3(-0, -1, -0),
        glm::vec3(-0, -1, -0),
        glm::vec3(-0, -0, -1),
        glm::vec3(-0, -0, -1),
        glm::vec3(-0, -0, -1),
        glm::vec3(-0, -0, 1),
        glm::vec3(-0, -0, 1),
        glm::vec3(-0, -0, 1),
        glm::vec3(-1, -0, -0),
        glm::vec3(-1, -0, -0),
        glm::vec3(-1, -0, -0),
        glm::vec3(-0, 1, -0),
        glm::vec3(-0, 1, -0),
        glm::vec3(-0, 1, -0),
        glm::vec3(1, -0, -0),
        glm::vec3(1, -0, -0),
        glm::vec3(1, -0, -0),
        glm::vec3(-0, -1, -0),
        glm::vec3(-0, -1, -0),
        glm::vec3(-0, -1, -0),
        glm::vec3(-0, -0, -1),
        glm::vec3(-0, -0, -1),
        glm::vec3(-0, -0, -1),
        glm::vec3(-0, -0, 1),
        glm::vec3(-0, -0, 1),
        glm::vec3(-0, -0, 1),
    };
    Mesh *cube = new Mesh(vertices, uvs, normals);
    cube->translate(pos);
    cube->rotate(rot.z, glm::vec3(0, 0, 1));
    cube->rotate(rot.y, glm::vec3(0, 1, 0));
    cube->rotate(rot.x, glm::vec3(1, 0, 0)); 
    cube->scale(glm::vec3(1, 1, 1));

    cube->setColorTexture(texture[0]);
    cube->setNormalTexture(texture[1]);
    cube->setShader(shader);
    return cube;
}

std::vector<Mesh*> house(glm::vec3 pos, glm::vec3 rot, Texture *house_text[], float house_reps, Texture *roof_text[], Shader *shader)
{
    std::vector<Mesh*> meshes;
    Mesh* base = cube(pos, rot, house_text, house_reps, shader);
    // base->setShader(shader);
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
    glm::mat4 model = base->getModel();
    Mesh* roof = new Mesh(roof_vertices, roof_uvs, roof_normals);
    roof->setModel(model);
    roof->translate(glm::vec3(0, 0.9, 0));
    roof->rotate(rot.y, glm::vec3(0, 1, 0));
    roof->rotate(rot.x, glm::vec3(1, 0, 0));
    roof->scale(glm::vec3(1.2, 1.2, 1.2));
    roof->setColorTexture(roof_text[0]);
    roof->setNormalTexture(roof_text[1]);
    roof->setShader(shader);
    meshes.push_back(base);
    meshes.push_back(roof);

    //torches
    float torchLength = 0.5;
    int torchAngle = -35;
    float torchPos = 0.7;
    float torchHeight = 0.4;
    float torchBallRadius = 0.1;
    Mesh* torch1 = cylinder(torchLength, 0.03, roof_text[0], shader);
    torch1->setModel(model);
    torch1->translate(glm::vec3(1, torchHeight, -torchPos));
    torch1->rotate(torchAngle, glm::vec3(0, 0, 1));
    meshes.push_back(torch1);

    //torch ball 1
    Sphere *torchBall1 = new Sphere(torchBallRadius, 10, 10);
    torchBall1->setModel(torch1->getModel());
    //based on the angle of the torch and the length, but the ball at the end of the torch
    torchBall1->translate(glm::vec3(0, torchLength, 0));

    torchBall1->setColorTexture(roof_text[0]);
    torchBall1->setNormalTexture(roof_text[1]);
    torchBall1->setShader(shader);
    meshes.push_back(torchBall1);


    Mesh* torch2 = cylinder(torchLength, 0.03, roof_text[0], shader);
    torch2->setModel(model);
    torch2->translate(glm::vec3(1, torchHeight, torchPos));
    torch2->rotate(torchAngle, glm::vec3(0, 0, 1));
    meshes.push_back(torch2);

    //torch ball 2
    Sphere *torchBall2 = new Sphere(torchBallRadius, 10, 10);
    torchBall2->setModel(torch2->getModel());
    //based on the angle of the torch and the length, but the ball at the end of the torch
    torchBall2->translate(glm::vec3(0, torchLength, 0));
    
    torchBall2->setColorTexture(roof_text[0]);
    torchBall2->setNormalTexture(roof_text[1]);
    torchBall2->setShader(shader);
    meshes.push_back(torchBall2);

    return meshes;
}

Mesh *sun(glm::vec3 pos, glm::vec3 rot, float shiny, int emission, Texture *texture)
{
    glPushMatrix();
    //  Offset
    glTranslated(pos.x, pos.y, pos.z);
    glRotated(rot.x, 1, 0, 0);
    glRotated(rot.y, 0, 1, 0);
    glRotated(rot.z, 0, 0, 1);
    // draw the sun
    glColor3f(1, 1, 0);
    //setup materials
    GLfloat mat_specular[] = {1.0, 1.0, 0.0, 1.0};
    glm::vec4 mat_emission = glm::vec4(0.01, 0.01, 0, 1) * static_cast<float>(emission);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shiny);
    glMaterialfv(GL_FRONT, GL_EMISSION, glm::value_ptr(mat_emission));

    sphere(zero, 0.5, texture);
    glPopMatrix();
}
Mesh* moon(glm::vec3 pos, glm::vec3 rot, float shiny, int emission, Texture *texture)
{
    glPushMatrix();
    GLfloat ambient[] = {0.8, 0.8, 0.8, 1.0};
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    //  Offset
    glTranslated(pos.x, pos.y, pos.z);
    glRotated(rot.x, 1, 0, 0);
    glRotated(rot.y, 0, 1, 0);
    glRotated(rot.z, 0, 0, 1);
    // draw the sun
    glColor3f(1, 1, 1);
    //setup materials
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    glm::vec4 mat_emission = glm::vec4(0.01, 0.01, 0.01, 1) * static_cast<float>(emission);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 70);
    glMaterialfv(GL_FRONT, GL_EMISSION, glm::value_ptr(mat_emission));

    sphere(zero, 1, texture);
    glPopMatrix();
}