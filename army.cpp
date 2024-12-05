//todo: day night
//todo: why is grass so green?
//todo: fix abbrupt change in color and lighting
#include "lib.h"
#include "Text.h"
#include "Camera.h"
#include "Texture.h"
#include <vector>
#include "Shader.h"
// #include "Mesh.h"
#include "shapes.h"
#include "objects/Cylinder.h"
#include "objects/Sphere.h"
#include "objects/Skybox.h"
#include "objects/House.h"

// settings
static void draw_screen(float deltaTime);
void handle_key_event(SDL_Event event);
void gl_error();
void resize(int width, int height);

int ph = 20;
int th = -90;
int w_width = 800;
int w_height = 600;
float aspect = (float)w_width / (float)w_height;
bool is_fullscreen = false;
SDL_Window *Window;
SDL_GLContext Context;
// Text arial = Text("arial.ttf", 24);
bool quit = false;

int leg_angle = 90;
bool leg_angle_backwards = false;
int arm_angle = 180;
bool arm_angle_backwards = false;

float march = 0.01;
int number_rows = 5;
int number_groups = 1;
bool show_commands = false;
int mode = 0;
bool lighting = true;
bool smooth = true;
bool local_viewer = true;
bool show_normals = false;

int ambient = 0;
int diffuse = 80;
int specular = 0;

int shine =  1;
int emission = 5;

bool stop_army = false;
bool stop_sun = false;

bool grab_mouse = false;


int sun_width = 7;

int fov = 57;
int dim = 10;
enum projection_types
{
    ORTHOGONAL,
    PERSPECTIVE,
    FIRST_PERSON,
    THIRD_PERSON
};
int projection = FIRST_PERSON;
std::string projection_names[] = {"Orthogonal", "Perspective", "First Person", "Third Person"};

// glm vertex camera position
Camera camera = Camera();
Camera camera3 = Camera();

bool solider_pov = false;
int solider = 0;

static void Projection()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (projection == PERSPECTIVE || projection == FIRST_PERSON || projection == THIRD_PERSON)
    {
        camera.SetProjectionMatrix(fov, dim, aspect);
    }
    else if (projection == ORTHOGONAL)
        glOrtho(-dim * aspect, dim * aspect, -dim * sqrt(2), dim * sqrt(2), -dim - sqrt(2), dim + sqrt(2));
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if (projection == FIRST_PERSON && grab_mouse)
    {
        // capture the mouse inside the window
        SDL_SetWindowGrab(Window, SDL_TRUE);
        // rotate the camera
        SDL_ShowCursor(SDL_DISABLE);
    }
    else
    {
        SDL_SetWindowGrab(Window, SDL_FALSE);
        SDL_ShowCursor(SDL_ENABLE);
    }
}


Shader *shader = nullptr;

int floor_div = 1;
bool texture = true;
Texture *grass = nullptr;
Texture *grass_normal = nullptr;
Texture *brick = nullptr;
Texture *brick_normal = nullptr;

Texture *roof = nullptr;
Texture *roof_normal = nullptr;

Texture *fire_texture = nullptr;
void cleanup()
{


    // SDL_GL_DeleteContext(Context);
    SDL_DestroyWindow(Window);
    SDL_Quit();

    //free the textures
}
std::vector<glm::vec3> lightPositions;
std::vector<Mesh*> houseMesh;
Mesh *plane = nullptr;
std::vector<std::vector<Mesh *>> houses(10);
Cylinder* cylinderMesh = nullptr;
Sphere* sphereMesh = nullptr;
Skybox* skybox = nullptr;
float lightPower = 1.0;
int main(int argc, char *argv[])
{
    // glfw: initialize and configure
    // ------------------------------
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "Error: %s\n", SDL_GetError());
        return -1;
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    //set compatibility profile
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

    // Turn on double buffering with a 24bit Z buffer
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    Window = SDL_CreateWindow("Textures - Caedin Cook", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w_width, w_height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | (is_fullscreen * SDL_WINDOW_FULLSCREEN));
    if (Window == NULL)
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Failed to create OpenGL window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create a OpenGL Context
    Context = SDL_GL_CreateContext(Window);
    if (Context == NULL)
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Failed to create OpenGL context: %s\n", SDL_GetError());
        SDL_DestroyWindow(Window);
        SDL_Quit();
        return 1;
    }


    //init GLEW
    glewExperimental = GL_TRUE;
    int init_res = glewInit();
    if (init_res != GLEW_OK)
    {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(init_res));
        return -1;
    }

   
        std::vector<glm::vec3> plane_vertices = {
        glm::vec3(1, 0, 1),
        glm::vec3(-1, 0, -1),
        glm::vec3(-1, 0, 1),
        glm::vec3(1, 0, 1),
        glm::vec3(1, 0, -1),
        glm::vec3(-1, 0, -1),
    };
    float plane_rep = 10;
    std::vector<glm::vec2> plane_uvs = {
        glm::vec2(plane_rep, 0),
        glm::vec2(0, plane_rep),
        glm::vec2(0, 0),
        glm::vec2(plane_rep, 0),
        glm::vec2(plane_rep, plane_rep),
        glm::vec2(0, plane_rep),
    };
    std::vector<glm::vec3> plane_normals = {
        glm::vec3(0, 1, 0),
        glm::vec3(0, 1, 0),
        glm::vec3(0, 1, 0),
        glm::vec3(0, 1, 0),
        glm::vec3(0, 1, 0),
        glm::vec3(0, 1, 0),
    };

    skybox = new Skybox(&camera);

    plane = new Mesh(plane_vertices, plane_uvs, plane_normals);

    grass = new Texture("./textures/grass/color.png");
    grass_normal = new Texture("./textures/grass/normal.png");

    // glEnable(GL_TEXTURE_2D);
    //initlaize Textures
    brick = new Texture("./textures/brick/color.jpg");
    brick_normal = new Texture("./textures/brick/normal.png");

    roof = new Texture("./textures/roof/color.jpg");
    roof_normal = new Texture("./textures/roof/normal.png");

    fire_texture = new Texture("./textures/fire/color.jpg");
    shader = new Shader("./shaders/basic.vert", "./shaders/basic.frag");
    if(shader->getError() != 0)
    {
        SDL_Log("Error: %d\n", shader->getError());
        return 1;
    }

    Texture *brick_textures[] = {brick, brick_normal};
    Texture *roof_textures[] = {roof, roof_normal};

    // houseMesh = house(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), brick_textures, 2, roof_textures, shader, lightPositions);
    std::vector<glm::vec3> lightPositionsTemp;
    int index = 0;
    for (int i = -10; i < 10; i += 4)
    {
        // house color based on i
        houses[index++] = house(glm::vec3(-6, 0.0, i + 1), glm::vec3(0,0,0), brick_textures, 1.0f, roof_textures, fire_texture, shader, lightPositions);
        lightPositionsTemp.push_back(glm::vec3(-6, 0.0, i + 1));
        // lightPositions.push_back(glm::vec3(-6, 0.0, i + 1));
        houses[index++] = house(glm::vec3(6, 0.0, i + 1), glm::vec3(0,180,0), brick_textures, 1.0, roof_textures, fire_texture, shader, lightPositions);
        lightPositionsTemp.push_back(glm::vec3(6, 0.0, i + 1));
    }
    // lightPositions = lightPositionsTemp;
    //check how many duploicate lights we have

    plane->setShader(shader);
    plane->setColorTexture(grass);
    plane->setNormalTexture(grass_normal);
    plane->translate(glm::vec3(0, -1, 0));
    plane->scale(glm::vec3(10, 1, 10));

    cylinderMesh = new Cylinder(.5, 0.03);
    cylinderMesh->setShader(shader);
    cylinderMesh->setColorTexture(brick);
    cylinderMesh->setNormalTexture(brick_normal);
    cylinderMesh->translate(glm::vec3(0, 0, 0));

    sphereMesh = new Sphere(0.5, 20, 20);
    sphereMesh->setShader(shader);
    sphereMesh->setColorTexture(brick);
    sphereMesh->setNormalTexture(brick_normal);
    sphereMesh->translate(glm::vec3(0, 2, 0));


    // ennable depth testing
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // initialize lorenz and fps counter
    unsigned int lastFrame = SDL_GetTicks();
    unsigned int fpsLast = SDL_GetTicks();
    unsigned int fpsCurrent = 0;
    unsigned int fpsCounter = 0;
    float deltaTime = 0.0f;
    resize(w_width, w_height); // initialize the viewport
    camera.SetPosition(glm::vec3(0, 0, 0));
    camera.LookAt(glm::vec3(0,-1,0));
    camera.SetAngle(-90, 0);
    while (!quit)
    {

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_RESIZED)
                {
                    w_width = event.window.data1;
                    w_height = event.window.data2;
                    // resize the viewport
                    resize(event.window.data1, event.window.data2);
                }
                break;
            default:
                handle_key_event(event);
                break;
            }
        }
        // delta time in seconds
        // float secs = deltaTime / 1000.0f;
        //  camera.SetSpeed(camera.GetSpeed() * secs);
        draw_screen(deltaTime);
        // get error
        gl_error();
        fpsCounter++;

        if (SDL_GetTicks() - fpsLast >= 1000)
        {
            fpsCurrent = fpsCounter;
            fpsCounter = 0;
            fpsLast = SDL_GetTicks();
            std::string title = "Army Perspective - Caedin Cook FPS: " + std::to_string(fpsCurrent);
            SDL_SetWindowTitle(Window, title.c_str());
            SDL_Log("FPS: %d\n", fpsCurrent);
        }
        deltaTime = SDL_GetTicks() - lastFrame;
        lastFrame = SDL_GetTicks();
        SDL_GL_SwapWindow(Window);
    }
    // sdl: terminate, clearing all previously allocated sdl resources.
    // ------------------------------------------------------------------
    cleanup();

    return 0;
}


float time_day = 0;
float time_speed = 0.1;
float accumulated_time = 0;
bool flashLightEnabled = false;
float getFlicker() {
    return (rand() % 100) / 500.0;
}
float flicker = getFlicker();
static void draw_screen(float deltaTime)
{
    accumulated_time += deltaTime;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if(lighting)
    {
        // }
        glClearColor(0.53, 0.81, 0.98, 1);
        lightPower = 1.0;
        // glm::vec4 Position(distance * Cos(time_day), distance * Sin(time_day), 0, 1);
     }
    else
    {
        glClearColor(0,0,0, 1);
        lightPower = 1;
    }
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = camera.GetProjectionMatrix();
    // glm::mat4 mvp = projection * view * model;
    glColor3f(1, 1, 1);

    shader->use();
    //set the uniforms
    shader->setMat4("projection", projection);
    shader->setMat4("view", view);
    int numLights = 20;
    shader->setInt("numLights", numLights);
    lightPositions[0] = camera.GetPosition();
    //set light power randomly so it appears to flicker
    if(accumulated_time > 700)
    {
        flicker = getFlicker();
        accumulated_time = 0;
    }
    for(int i = 0; i<numLights; i++){
        std::string lightName = "lights[" + std::to_string(i+1) + "]";
        shader->setVec3(lightName + ".pos", lightPositions[i]);
        // shader->setFloat(lightName + ".power", 5.0);
        // shader->setVec4(lightName + ".color", glm::vec4(1, 1, 1, 1));
        if(accumulated_time > 700)
        {
            flicker = getFlicker();
        }
        shader->setFloat(lightName+".power", 0.7 + flicker);
            //set the color between orange and red like a torch
        shader->setVec4(lightName+".color", glm::vec4(1, 0.1, 0, 1));
    }
    if(accumulated_time > 700)
    {
        flicker = getFlicker();
        accumulated_time = 0;
    }
//     struct FlashLight {
//     vec3 position;  
//     vec3 direction;
//     float cutOff;
//     float outerCutOff;
  
//     vec3 ambient;
//     vec3 diffuse;
//     vec3 specular;
	
//     float constant;
//     float linear;
//     float quadratic;
// };
    shader->setBool("flashLightEnabled", flashLightEnabled);
    shader->setVec3("flashLight.light.pos", camera.GetPosition());
    shader->setVec4("flashLight.light.color", glm::vec4(1, 1, 1, 1));
    // shader->setVec3("flashLight.ambient", glm::vec3(0.1, 0.1, 0.1));
    // shader->setVec3("flashLight.diffuse", glm::vec3(0.8, 0.8, 0.8));
    // shader->setVec3("flashLight.specular", glm::vec3(1, 1, 1));
    shader->setFloat("flashLight.light.power", lightPower);
    shader->setVec3("flashLight.dir", camera.GetDirection());
    shader->setFloat("flashLight.cutOff", cos(glm::radians(12.5f)));

    plane->draw();
    // for(auto house : houseMesh)
    // {
    //     house->draw();
    // }

    for(auto house : houses)
    {
        for(auto mesh : house)
        {
            mesh->draw();
        }
    }
    skybox->getShader()->use();
    skybox->getShader()->setMat4("projection", projection);
    skybox->getShader()->setMat4("view", view);
    skybox->draw();

    // cylinderMesh->draw();
    // sphereMesh->draw();
    glUseProgram(0);
    glLoadIdentity();
    camera.Look();

    // glBegin(GL_QUADS);
    // glColor3f(1, 0, 0);
    // glVertex3f(-2, -1, -2);
    // glVertex3f(-2, -1, 2);
    // glVertex3f(2, -1, 2);
    // glVertex3f(2, -1, -2);
    // glEnd();

    glFlush();
}
bool move_toggle = false;
void handle_key_event(SDL_Event event)
{
    if(event.type == SDL_KEYDOWN && event.key.keysym.sym ==  SDLK_w)
    {
        camera.MoveForward();
    }
    if(event.type == SDL_KEYDOWN && event.key.keysym.sym ==  SDLK_s)
    {
        camera.MoveBackward();
    }
    if(event.type == SDL_KEYDOWN && event.key.keysym.sym ==  SDLK_a)
    {
        camera.MoveLeft();
    }
    if(event.type == SDL_KEYDOWN && event.key.keysym.sym ==  SDLK_d)
    {
        camera.MoveRight();
    }
    if(event.type == SDL_KEYDOWN && event.key.keysym.sym ==  SDLK_SPACE)
    {
        if(SDL_GetModState() & KMOD_CTRL)
        {
            camera.MoveDown();
        }
        else
        {
            camera.MoveUp();
        }
    }
        //toggle move toggle if cntrl is pressed
    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            SDL_Log("Escape key pressed\n");
            cleanup();
            quit = true;
            break;
        case SDLK_c:
            show_commands = !show_commands;
            break;
        case SDLK_F11:
            is_fullscreen = !is_fullscreen;
            SDL_SetWindowFullscreen(Window, is_fullscreen ? SDL_WINDOW_FULLSCREEN : 0);
            break;
        case SDLK_m:
            if(SDL_GetModState() & KMOD_SHIFT)
            {
                projection++;
                projection %= 4;
                Projection();
            }
            else
            {
                projection--;
                projection = projection < 0 ? 3 : projection;
                Projection();
            }
            break;
        case SDLK_o:
            if (SDL_GetModState() & KMOD_SHIFT)
            {
                mode++;
                mode %= 4;
            }
            else
            {
                mode--;
                mode = mode < 0 ? 3 : mode;
            }
            break;
        case SDLK_1:
            camera.SetSpeed(camera.GetSpeed() + 0.1);
            break;
        case SDLK_2:
            camera.SetSpeed(camera.GetSpeed() - 0.1);
            break;
        case SDLK_SEMICOLON:
            lighting = !lighting;
            break;
        case SDLK_k:
            smooth = !smooth;
            break;
        case SDLK_j:
            local_viewer = !local_viewer;
            break;
        case SDLK_n:
            show_normals = !show_normals;
            break;
        case SDLK_p:
            if(SDL_GetModState() & KMOD_SHIFT)
            {
                stop_army = !stop_army;
            }
            else
            {
                stop_sun = !stop_sun;
            }
            break;
        case SDLK_t:
            if(SDL_GetModState() & KMOD_SHIFT)
            {
                time_speed -= 0.01;
                time_speed = std::max(0.01f, time_speed);
            }
            else
            {
                time_speed += 0.01;
                time_speed = std::min(1.0f, time_speed);

            }
        case SDLK_r:
            if(SDL_GetModState() & KMOD_SHIFT)
            {
                time_day = 180;
            }
            else
            {
                time_day = 0;
            }
            break;
        case SDLK_l:
            if(SDL_GetModState() & KMOD_SHIFT)
            {
                lightPower += 0.1;
            }
            else
            {
                lightPower -= 0.1;
            }
            break;
        case SDLK_f:
            flashLightEnabled = !flashLightEnabled;
            break;
        case SDLK_y:
            texture = !texture;
            break;

        case SDLK_g:
            grab_mouse = !grab_mouse;
            break;
        default:
            break;
        }
        //if cntrl is pressed go down
    }
    // if scroll wheel
    else if (event.type == SDL_MOUSEWHEEL)
    {
        // change the fov
        if (projection == PERSPECTIVE || projection == FIRST_PERSON)
        {
            fov += event.wheel.y;
            fov = std::max(1, fov);
            fov = std::min(180, fov);
            Projection();
        }
        else if (projection == ORTHOGONAL)
        {
            dim += event.wheel.y;
            dim = std::max(1, dim);
            dim = std::min(20, dim);
            Projection();
        }
    }
    // change ph and th by mouse movement and mouse button one being held down
    else if (event.type == SDL_MOUSEMOTION && ((event.motion.state & SDL_BUTTON_LMASK) || projection == FIRST_PERSON))
    {
        if (projection != FIRST_PERSON)
        {
            th += event.motion.xrel;
            ph += event.motion.yrel;
            th %= 360;
            ph %= 360;
        }
        else
        {
            camera.ChangeAngle(event.motion.xrel, -event.motion.yrel);
        }
    }
    //else if cntrl is pressed

}
void gl_error()
{
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR)
    {
        SDL_Log("OpenGL error: %s\n", gluErrorString(err));
    }
}

void resize(int width, int height)
{
    w_width = width;
    w_height = height;
    aspect = (float)width / (float)height;
    glViewport(0, 0, width, height);
    // set frustum
    Projection();
    // update the font so it can display properly
    // arial.UpdateFont(24, width, height);
}