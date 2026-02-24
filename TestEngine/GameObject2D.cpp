#include "GameObject2D.h"

GameObject2D::GameObject2D(float xPos, float yPos, uint8_t layer) : GameObject(xPos, yPos, layer)
{
	this->layer = layer;
}

GameObject2D::GameObject2D(glm::vec2 pos, uint8_t layer) : GameObject(glm::vec3(pos, layer))
{
	this->layer = layer;
}

void GameObject2D::addChild(std::shared_ptr<GameObject2D> obj, std::string name)
{
	GameObject::addChild(obj, name);
}
