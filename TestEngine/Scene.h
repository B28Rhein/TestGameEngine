#pragma once
#include <vector>
#include <queue>
#include "GameObject.h"

class Scene
{
	std::vector<Entry<GameObject>> Objects;
	std::vector<GameObject*> collapseTree(GameObject* go);
public:
	Scene();
	void AddObject(std::shared_ptr<GameObject> go, std::string name);
	GameObject* GetObjectByName(std::string name);
	std::vector<Entry<GameObject>>* GetObjects();
	std::vector<GameObject*> GetCollapsedObjectTree();
	void RemoveObject(std::string name);
	bool IsOfName(std::string name);
	~Scene();
};

