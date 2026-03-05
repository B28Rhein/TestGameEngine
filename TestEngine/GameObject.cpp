#include "GameObject.h"

GameObject::GameObject(float xpos, float ypos, float zpos)
{
	auto pos = glm::vec3(xpos, ypos, zpos);
	AddComponent<TransformComponent>();
	GetComponent<TransformComponent>()->SetTransform(pos, glm::vec3(0), glm::vec3(1));
	parent = nullptr;
	children = std::vector<Entry<GameObject>>();
}

GameObject::GameObject(glm::vec3 nPos) {
	AddComponent<TransformComponent>();
	GetComponent<TransformComponent>()->SetTransform(nPos, glm::vec3(0), glm::vec3(1));
	parent = nullptr;
	children = std::vector<Entry<GameObject>>();
}

void GameObject::addChild(std::shared_ptr<GameObject> obj, std::string name)
{
	std::string newName = name;
	int iter = 0;
	while (IsOfName(newName)) {
		newName = name + std::to_string(iter);
		iter++;
	}
	obj->parent = this;
	children.emplace_back(newName, obj);
}

void GameObject::removeChild(std::string name)
{
	for (int i = 0; i < children.size(); i++) {
		if (children[i].name == name) {
			children.erase(children.begin() + i);
			return;
		}
		children[i].Object->removeChild(name);
	}
}

std::vector<Entry<GameObject>> GameObject::getChildren()
{
	return children;
}

GameObject* GameObject::getParent()
{
	return parent;
}

GameObject::~GameObject()
{
}

bool GameObject::IsOfName(std::string name)
{
	for (auto& obj : children) {
		if (obj.name == name) {
			return true;
		}
	}
	return false;
}