#include "Camera2D.h"


Camera2D::Camera2D(float speed, float sensitivity,
	glm::vec2 cameraPos,
	std::pair<float, float> _WindowSize = std::pair<float, float>(800, 600),
	CameraMode CM)
	: GameObject2D(cameraPos, 3), AbstractCamera(speed, sensitivity,glm::vec3(cameraPos, 3), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0, 1, 0), CM, _WindowSize)
{
}

glm::mat4 Camera2D::getLookAt()
{
	return glm::lookAt(pos, pos + front, up);
}

glm::mat4 Camera2D::getPerspective()
{
	if (cameraMode == CameraMode::Camera2DOrtho) {
		return glm::ortho(-WindowSize.first / 2, WindowSize.first / 2, -WindowSize.second / 2, WindowSize.second / 2, 0.1f, 100.0f);
	}
	else {
		return glm::perspective(glm::radians(fov), WindowSize.first / WindowSize.second, 0.1f, 100.0f);
	}
}

void Camera2D::moveCamera(int direction, float deltaTime)
{
	glm::vec3 moveVector = glm::vec3(0.0f, 0.0f, 0.0f);
	moveVector += glm::vec3(0.0f, 1.0f, 0.0f) * (float)(direction % 2);
	direction >>= 1;
	moveVector -= glm::vec3(0.0f, 1.0f, 0.0f) * (float)(direction % 2);
	direction >>= 1;
	moveVector -= glm::normalize(glm::cross(front, up)) * (float)(direction % 2);
	direction >>= 1;
	moveVector += glm::normalize(glm::cross(front, up)) * (float)(direction % 2);
	direction >>= 1;
	float currentSpeed = cameraSpeed + cameraSpeed * direction;
	if (moveVector != glm::vec3(0.0f))
	{
		moveVector = glm::normalize(moveVector) * currentSpeed * deltaTime;
		GameObject::moveToPosition(pos + moveVector);
	}
}

void Camera2D::rotateCamera(float xOffset, float yOffset)
{
	return;
}

void Camera2D::zoomCamera(float xOffset, float yOffset)
{
	return;
}
