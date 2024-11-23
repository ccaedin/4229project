#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aUV;
layout(location = 2) in vec3 aNormal;
layout(location = 3) in vec3 aTangent;
layout(location = 4) in vec3 aBitangent;

out vec2 UV;
out vec3 positionWorld;
out vec3 cameraDirectionCamera;
out vec3 lightDirectionCamera;

out vec3 lightDirectionTangent;
out vec3 cameraDirectionTangent;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPos;

void main()
{
    mat4 mvp = projection * view * model;
    mat3 mv3x3 = mat3(view * model);     

    gl_Position =  mvp * vec4(aPos,1);

    positionWorld = vec3(model * vec4(aPos, 1.0));

    //cameraDirectionCamera
    vec3 vertex_Camera = vec3(view * model * vec4(aPos, 1.0));
    cameraDirectionCamera = vec3(0.0, 0.0, 0.0) - vertex_Camera;

    //vert to light in camera space
    vec3 light_Camera = vec3(view * vec4(lightPos, 1.0));
    lightDirectionCamera = light_Camera + cameraDirectionCamera;

    UV = aUV;

    //model to camera
    vec3 vertexTangetCamera  = mv3x3 * aTangent;
    vec3 vertexBitangentCamera = mv3x3 * aBitangent;
    vec3 vertexNormalCamera = mv3x3 * aNormal;

    mat3 TBN = transpose(mat3(
        vertexTangetCamera,
        vertexBitangentCamera,
        vertexNormalCamera
    ));

    lightDirectionTangent = TBN * lightDirectionCamera;
    cameraDirectionTangent = TBN * cameraDirectionCamera;
    
}
