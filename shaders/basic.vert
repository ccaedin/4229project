#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aUV;
layout(location = 2) in vec3 aNormal;
layout(location = 3) in vec3 aTangent;
layout(location = 4) in vec3 aBitangent;

out vec2 UV;
out vec3 positionWorld;
out vec3 cameraDirectionCamera;

out vec3 cameraDirectionTangent;

#define MAX_LIGHTS 5
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPos[MAX_LIGHTS];
uniform float lightPower;
uniform int numLights;
struct Light {
	vec3 pos;
	float power;
    vec3 directionCamera;
    vec3 directionTangent;
};
out Light lights[MAX_LIGHTS];

void calculateLight(int index, mat4 view, vec3 cameraDirectionCamera, mat3 TBN)
{
    lights[index] = Light(lightPos[index], lightPower, vec3(0,0,0), vec3(0,0,0));
    vec3 light_Camera = vec3(view * vec4(lights[index].pos, 1.0));
    lights[index].directionCamera = light_Camera + cameraDirectionCamera;
    lights[index].directionTangent = TBN * lights[index].directionCamera;
}

void main()
{
    mat4 mvp = projection * view * model;
    mat3 mv3x3 = mat3(view * model);     

    gl_Position =  mvp * vec4(aPos,1);
    
    positionWorld = vec3(model * vec4(aPos, 1.0));

    //cameraDirectionCamera
    vec3 vertex_Camera = vec3(view * model * vec4(aPos, 1.0));
    cameraDirectionCamera = vec3(0.0, 0.0, 0.0) - vertex_Camera;
    
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
    for(int i = 0; i < numLights; i++)
    {
        calculateLight(i, view, cameraDirectionCamera, TBN);
    }
    cameraDirectionTangent = TBN * cameraDirectionCamera;
    
}
