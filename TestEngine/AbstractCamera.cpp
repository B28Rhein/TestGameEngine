#include "AbstractCamera.h"

AbstractCamera::AbstractCamera(float speed, float sensitivity, glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp, CameraMode mode, std::pair<float, float> _WindowSize)
{
	this->cameraSpeed = speed;
	this->sensitivity = sensitivity;
	front = cameraFront;
	up = cameraUp;
	pitch = 0.0f;
	yaw = -90.0f;
	roll = 0;
	fov = 45.0f;
	cameraMode = mode;
	WindowSize = _WindowSize;
}

void AbstractCamera::setWindowSize(std::pair<float, float> _WindowSize)
{
	WindowSize = _WindowSize;
}
