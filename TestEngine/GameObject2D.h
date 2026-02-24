#pragma once
#include "GameObject.h"
#include <glm/glm.hpp>

class GameObject2D : public GameObject
{
	uint8_t layer;
public:
	GameObject2D(float xPos, float yPos, uint8_t layer);
	GameObject2D(glm::vec2 pos, uint8_t layer);
	void addChild(std::shared_ptr<GameObject2D> obj, std::string name);
};

