#include "Camera.h"
Camera::Camera(float speed, float sensitivity,
	glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp,
	CameraMode mode = CameraMode::Flying3DCamera, std::pair<float, float> _WindowSize = std::pair<float, float>(800, 600))
	: GameObject(cameraPos), AbstractCamera(speed, sensitivity, cameraPos, cameraFront, cameraUp,  mode, _WindowSize)
{

}

glm::mat4 Camera::getLookAt()
{
	return glm::lookAt(pos, pos + front, up);
}

glm::mat4 Camera::getPerspective()
{
	return glm::perspective(glm::radians(fov), WindowSize.first / WindowSize.second, 0.1f, 100.0f);
}

void Camera::moveCamera(int direction, float deltaTime)
{
	glm::vec3 moveFront = front;
	if (cameraMode == CameraMode::fps3DCamera)
	{
		moveFront.y = 0.0f;
	}
	glm::vec3 moveVector = glm::vec3(0.0f, 0.0f, 0.0f);
	moveVector += moveFront * (float)(direction % 2);
	direction >>= 1;
	moveVector -= moveFront * (float)(direction % 2);
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

void Camera::rotateCamera(float xOffset, float yOffset)
{
	xOffset *= sensitivity;
	yOffset *= sensitivity;

	yaw += xOffset;
	pitch += yOffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(direction);
}

void Camera::zoomCamera(float xOffset, float yOffset)
{
	fov -= yOffset;
	if (fov < 1.0f)
		fov = 1.0f;
	if (fov > 45.0f)
		fov = 45.0f;
}
