#include "CameraComponent.h"

CameraComponent::CameraComponent() : Component(nullptr)
{
    cameraOffset = glm::vec3(0.0f, 0.0f, 3.0f);
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);
    pitch = 0.0f;
    yaw = -90.0f;
    roll = 0;
    fov = 45.0f;
    projectionType = CameraProjectionType::perspective;
}

CameraComponent::CameraComponent(GameObject* go) : Component(go)
{
    cameraOffset = glm::vec3(0.0f, 0.0f, 3.0f);
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);
    pitch = 0.0f;
    yaw = -90.0f;
    roll = 0;
    fov = 45.0f;
    projectionType = CameraProjectionType::perspective;
}

void CameraComponent::setPitchYawRoll(float pitch, float yaw, float roll)
{
    this->pitch = pitch;
    this->yaw = yaw;
    this->roll = roll;
}

void CameraComponent::setPitchYawRoll(glm::vec3 values)
{
    pitch = values.x;
    yaw = values.y;
    roll = values.z;
}

void CameraComponent::setOffset(glm::vec3 offset)
{
    this->cameraOffset = offset;
}

void CameraComponent::setFront(glm::vec3 front)
{
    this->front = front;
}

void CameraComponent::setUpVector(glm::vec3 up)
{
    this->up = up;
}

void CameraComponent::setProjectionType(CameraProjectionType type)
{
    projectionType = type;
}

void CameraComponent::setProjectionType(int type)
{
    projectionType = CameraProjectionType(type);
}

void CameraComponent::setFov(float fov)
{
    this->fov = fov;
}

float CameraComponent::getFov()
{
    return fov;
}

CameraProjectionType CameraComponent::getType()
{
    return projectionType;
}

glm::vec3 CameraComponent::getPitchYawRoll()
{
    return glm::vec3(pitch, yaw, roll);
}

glm::vec3 CameraComponent::getOffset()
{
    return cameraOffset;
}

glm::vec3 CameraComponent::getFront()
{
    return front;
}

glm::vec3 CameraComponent::getUpVector()
{
    return up;
}
