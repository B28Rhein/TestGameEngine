#pragma once
#include <glm/glm.hpp>
#include "Component.h"
#include "GameObject.h"

class TransformComponent : public Component
{
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
public:
	TransformComponent(GameObject* go);
	glm::vec3 GetPos();
	glm::vec3 GetRot();
	glm::vec3 GetScale();
	void SetPos(glm::vec3 nPos);
	void SetRot(glm::vec3 nRot);
	void SetScale(glm::vec3 nScale);
	void SetTransform(glm::vec3 nPos, glm::vec3 nRot, glm::vec3 nScale);
	void ChangePosBy(glm::vec3 addPos);
	void ChangeRotBy(glm::vec3 addRot);
	void ChangeScaleBy(glm::vec3 addScale);
};

