#pragma once
#include <vector>
#include <queue>
#include "GameObject.h"

class Scene
{
	std::vector<Entry<GameObject>> Objects;
public:
	Scene();
	void AddObject(std::shared_ptr<GameObject> go, std::string name);
	Entry<GameObject> GetObjectByName(std::string name);
	std::vector<Entry<GameObject>>* GetObjects();
	void RemoveObject(std::string name);
	bool IsOfName(std::string name);
	~Scene();
};

