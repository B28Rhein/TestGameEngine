#pragma once
#include <glm/ext/vector_float3.hpp>
#include <utility>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>

enum class CameraMode
{
	Flying3DCamera = 0,
	fps3DCamera = 1,
	Camera2DOrtho = 2,
	Camera2DPerspective = 3,
};

class AbstractCamera
{
protected:
	float cameraSpeed;
	float pitch, yaw, roll;
	float fov;
	float sensitivity;
	std::pair<float, float> WindowSize;
	CameraMode cameraMode;
	glm::vec3 front;
	glm::vec3 up;
public:
	AbstractCamera(float speed, float sensitivity, glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp, CameraMode mode, std::pair<float, float> _WindowSize);
	void setWindowSize(std::pair<float, float> _WindowSize);
	virtual void zoomCamera(float xOffset, float yOffset) = 0;
	virtual void rotateCamera(float xOffset, float yOffset) = 0;
	virtual void moveCamera(int direction, float deltaTime) = 0;
	virtual glm::mat4 getPerspective() = 0;
	virtual glm::mat4 getLookAt() = 0;
};

