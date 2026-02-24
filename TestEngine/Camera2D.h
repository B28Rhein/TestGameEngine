#pragma once
#include "GameObject2D.h"
#include "AbstractCamera.h"
class Camera2D :
    public GameObject2D, public AbstractCamera
{

public:
	Camera2D(float speed, float sensitivity, glm::vec2 cameraPos, std::pair<float, float> _WindowSize, CameraMode CM = CameraMode::Camera2DOrtho);
	glm::mat4 getLookAt() override;
	glm::mat4 getPerspective() override;
	void moveCamera(int direction, float deltaTime) override;
	void rotateCamera(float xOffset, float yOffset) override;
	void zoomCamera(float xOffset, float yOffset) override;
};

