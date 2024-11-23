#ifndef CAMERA_H
#define CAMERA_H

#pragma once
#include "glm/glm.hpp"
class Camera
{
public:
    Camera();
    ~Camera();

    void SetPosition(glm::vec3 pos);
    void SetAngle(float yaw, float pitch);
    void MoveForward();
    void MoveBackward();
    void MoveLeft();
    void MoveRight();
    void MoveUp();
    void MoveDown();
    void ChangeAngle(float dYaw, float dPitch);
    void ChangePosition(glm::vec3 dPos);
    void Look();
    void SetSpeed(float speed);

    void LookAt(glm::vec3 target);

    void SetProjectionMatrix(int fov, int dim, int aspect);
    glm::mat4 GetProjectionMatrix() { return projection; }
    glm::mat4 GetViewMatrix() { return view; }
    glm::vec3 GetPosition();
    glm::vec3 GetDirection();
    glm::vec2 GetAngle();
    float GetSpeed();

    void Move(float x, float y, float z);
private:
    glm::vec3 camera_pos = glm::vec3(0.0f, 20.0f, 0.0f);
    glm::vec3 camera_front = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 camera_up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 camera_direction = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 camera_forward = glm::vec3(0.0f, 0.0f, -1.0f);
    float camera_yaw = -90.0f;
    float camera_pitch = 0.0f;
    float camera_speed = 0.05f;
    int fov = 57;
    int dim = 5;
    glm::mat4 projection;
    glm::mat4 view;
};

#endif // CAMERA_H
