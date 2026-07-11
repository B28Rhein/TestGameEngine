#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <vector>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include "AbstractRenderer.h"
#include "DrawableComponent.h"
#include "SpriteComponent.h"
#include "TextureComponent.h"
#include "Game.h"
class SpriteRenderer :
    public AbstractRenderer
{
public:
	SpriteRenderer(bool stbiFlipVert);
	void Render(GameObject*, glm::mat4 view, glm::mat4 projection);
	glm::mat4 GetObjectsModel(GameObject* go);
};

