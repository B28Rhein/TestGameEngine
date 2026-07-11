#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include "Window.h"
#include <vector>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include "GameObject.h"
#include "Game.h"
#include "AbstractRenderer.h"
#include "MeshComponent.h"


class Renderer3D : public AbstractRenderer
{
public:
	Renderer3D(bool stbiFlipVert);
	void Render();
	glm::mat4 GetObjectsModel(GameObject* go);
};

