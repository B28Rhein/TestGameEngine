#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "GameObject.h"
#include "AbstractCamera.h"



class Camera : public GameObject, public AbstractCamera
{
public:
	Camera(float speed, float sensitivity, glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp, CameraMode mode, std::pair<float, float> _WindowSize);
	glm::mat4 getLookAt() override;
	glm::mat4 getPerspective() override;
	void moveCamera(int direction, float deltaTime) override;
	void rotateCamera(float xOffset, float yOffset) override;
	void zoomCamera(float xOffset, float yOffset) override;
};


