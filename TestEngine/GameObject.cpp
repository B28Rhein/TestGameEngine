#include "GameObject.h"

GameObject::GameObject(float xpos, float ypos, float zpos)
{
	pos = glm::vec3(xpos, ypos, zpos);
	parent = nullptr;
	children = std::vector<Entry<GameObject>>();
}

GameObject::GameObject(glm::vec3 nPos) {
	pos = nPos;
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

// TODO: MAKE POSITION OF CHILDREN RELATIVE TO POSITION OF PARENT
void GameObject::moveToPosition(glm::vec3 position)
{
	for (auto& c : children) {
		glm::vec3 vec = c.Object->pos - pos;
		c.Object->pos = position + vec;
	}
	pos = position;
}

void GameObject::moveToPosition(float X, float Y, float Z)
{
	moveToPosition(glm::vec3(X, Y, Z));
}

void GameObject::Draw(glm::mat4 view, glm::mat4 projection) {
	MeshComponent* MC = GetComponent<MeshComponent>();
	if (MC != nullptr) {
		MC->Draw(view, projection, pos);
	}
	for (auto& oe : children) {
		auto c = oe.Object;
		c->Draw(view, projection);
	}
}

glm::vec3 GameObject::getPos()
{
	return pos;
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