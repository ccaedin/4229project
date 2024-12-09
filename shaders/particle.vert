#version 330 core

layout(location = 0) in vec3 vertices;
layout(location = 1) in vec3 position;
// layout(location = 2) in uint size;

out vec4 ParticleColor;

uniform mat4 projection;
uniform mat4 view;

uniform vec3 CameraRight_worldspace;
uniform vec3 CameraUp_worldspace;


uniform vec3 color;
uniform vec3 offset;

void main()
{
    ParticleColor = vec4(color, 1.0);

    vec3 vertPos_World = position + vertices * 0.03/2;
    // + CameraRight_worldspace * vertices.x * 1;// * size 
    // + CameraUp_worldspace * vertices.y * 1;// * size;

    gl_Position = projection * view * vec4(vertPos_World + offset, 1.0);

    ParticleColor = vec4(color, 1.0);
}