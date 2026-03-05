#pragma once
#include "Component.h"
#include <glm/glm.hpp>
enum class CameraProjectionType {
	ortho,
	perspective
};

class CameraComponent : public Component
{
	float pitch, yaw, roll, fov;
	CameraProjectionType projectionType;
	glm::vec3 cameraOffset;
	glm::vec3 front;
	glm::vec3 up;
public:
	CameraComponent();
	CameraComponent(GameObject* go);
	void setPitchYawRoll(float pitch, float yaw, float roll);
	void setPitchYawRoll(glm::vec3 values);
	void setOffset(glm::vec3 offset);
	void setFront(glm::vec3 front);
	void setUpVector(glm::vec3 up);
	void setProjectionType(CameraProjectionType type);
	void setProjectionType(int type);
	void setFov(float fov);
	float getFov();
	CameraProjectionType getType();
	glm::vec3 getPitchYawRoll();
	glm::vec3 getOffset();
	glm::vec3 getFront();
	glm::vec3 getUpVector();
};

