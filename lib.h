#ifndef LIB_H
#define LIB_H

#pragma once
#define GL_GLEXT_PROTOTYPES

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_opengl.h>
// Tell Xcode IDE to not gripe about OpenGL deprecation
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#else
#include <GL/glew.h>
// #include <GL/glut.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
// #include <GL/gl.h>
// #include <GL/glu.h>
#endif

#include <iostream>
#include <string>
#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#define PI 3.14159265359

#define Cos(x) (cos((x) * 3.14159265 / 180))
#define Sin(x) (sin((x) * 3.14159265 / 180))

extern bool show_normals; // show normals

#endif // LIB_H

