#include "lib.h"
#include "Camera.h"

// Constructor
Camera::Camera()
{

}

// Destructor
Camera::~Camera()
{

}

// Set the position of the camera
void Camera::SetPosition(glm::vec3 pos)
{
    camera_pos = pos;
}
void Camera::SetAngle(float yaw, float pitch)
{
    camera_yaw = yaw;
    camera_pitch = pitch;
}
void Camera::SetSpeed(float speed)
{
    camera_speed = speed;
}
// Move the camera forward
void Camera::MoveForward()
{
    glm::vec3 c = glm::normalize(camera_front) * camera_speed;
    c.y = 0;
    camera_pos += c; 
    // camera_pos.y = 1.5;
}

void Camera::MoveBackward()
{
    glm::vec3 c = glm::normalize(camera_front) * camera_speed;
    c.y = 0;
    camera_pos -= c;
    // camera_pos.y = 1.5;
}

void Camera::MoveLeft()
{
    camera_pos -= glm::normalize(glm::cross(camera_front,  camera_up)) * camera_speed;
}

void Camera::MoveRight()
{
    camera_pos += glm::normalize(glm::cross(camera_front, camera_up)) * camera_speed;
}

void Camera::MoveUp()
{
    camera_pos += camera_speed * camera_up;
}

void Camera::MoveDown()
{
    camera_pos -= camera_speed * camera_up;
}

// Change the angle of the camera
void Camera::ChangeAngle(float dYaw, float dPitch)
{
    camera_yaw += dYaw;
    camera_pitch += dPitch;
    if(camera_pitch > 89.0f)
        camera_pitch = 89.0f;
    if(camera_pitch < -89.0f)
        camera_pitch = -89.0f;
}

glm::vec3 Camera::GetDirection()
{
    return camera_front;
}

void Camera::Look()
{
    camera_direction.x = cos(glm::radians(camera_yaw)) * cos(glm::radians(camera_pitch));
    camera_direction.y = sin(glm::radians(camera_pitch));
    camera_direction.z = sin(glm::radians(camera_yaw)) * cos(glm::radians(camera_pitch));
    camera_front = glm::normalize(camera_direction);
    glm::vec3 c = camera_pos + camera_front;
    view = glm::lookAt(camera_pos, c, camera_up);
    // gluLookAt(camera_pos.x, camera_pos.y, camera_pos.z, c.x, c.y, c.z, camera_up.x, camera_up.y, camera_up.z);
    glLoadMatrixf(glm::value_ptr(view));
}

void Camera::LookAt(glm::vec3 target)
{
    camera_yaw = atan2(target.z - camera_pos.z, target.x - camera_pos.x);
    camera_pitch = atan2(target.y - camera_pos.y, sqrt((target.x - camera_pos.x) * (target.x - camera_pos.x) + (target.z - camera_pos.z) * (target.z - camera_pos.z)));
    camera_front = glm::normalize(target - camera_pos);
    glm::vec3 c = camera_pos + camera_front;
    gluLookAt(camera_pos.x, camera_pos.y, camera_pos.z, c.x, c.y, c.z, camera_up.x, camera_up.y, camera_up.z);
    view = glm::lookAt(camera_pos, c, camera_up);

}

void Camera::SetProjectionMatrix(int fov, int dim, int aspect)
{
    //ignore dim for now
    this->fov = fov;
    this->dim = 6;
    dim = 6;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov, aspect, 0.01, 5*dim);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    projection = glm::perspective(glm::radians((float)fov), (float)aspect, 0.01f, (float)5*dim);
}

glm::vec3 Camera::GetPosition()
{
    return camera_pos;
}

float Camera::GetSpeed()
{
    return camera_speed;
}
glm::vec2 Camera::GetAngle()
{
    return glm::vec2(camera_yaw, camera_pitch);
}