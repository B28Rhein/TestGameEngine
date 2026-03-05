#pragma once

class GameObject;

class Component
{
protected:
public:
	GameObject* gameObject;
	Component(GameObject* go);
	virtual ~Component();
};

