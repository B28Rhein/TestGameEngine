#pragma once

class GameObject;

class Component
{
protected:
	GameObject* gameObject;
public:
	Component(GameObject* go);
	virtual ~Component();
};

