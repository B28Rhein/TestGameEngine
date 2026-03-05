#include "Game.h"


std::vector<GameObject*> Scene::collapseTree(GameObject* go)
{
	std::vector<GameObject*> tree = std::vector<GameObject*>();
	if (go->getChildren().size() == 0) {
		return tree;
	}
	for (auto ch : go->getChildren())
	{
		tree.push_back(ch.Object.get());
		std::vector<GameObject*> t = collapseTree(ch.Object.get());
		for (auto c : t) {
			tree.push_back(c);
		}
	}
	return tree;
}

Scene::Scene()
{
}

void Scene::AddObject(std::shared_ptr<GameObject> go, std::string name)
{
	std::string newName = name;
	int iter = 0;
	while (IsOfName(newName)) {
		newName = name + std::to_string(iter);
		iter++;
	}
	Objects.emplace_back(newName, go);
}

GameObject* Scene::GetObjectByName(std::string name)
{
	std::queue<Entry<GameObject>> q;
	for (auto& ge : Objects) {
		q.push(ge);
	}
	do {
		if (q.front().name == name) {
			return q.front().Object.get();
		}
		auto go = q.front().Object;
		q.pop();
		for (auto& c : go->getChildren()) {
			q.push(c);
		}
	} while (!q.empty());
	return nullptr;
}

std::vector<Entry<GameObject>>* Scene::GetObjects()
{
	return &Objects;
}

std::vector<GameObject*> Scene::GetCollapsedObjectTree()
{
	std::vector<GameObject*> tree = std::vector<GameObject*>();
	for (auto go : Objects) {
		tree.push_back(go.Object.get());
		std::vector<GameObject*> t = collapseTree(go.Object.get());
		for (auto c : t) {
			tree.push_back(c);
		}
	}
	return tree;
}

void Scene::RemoveObject(std::string name)
{
	if (GetObjectByName(name) != nullptr) {
		for (int i = 0; i < Objects.size(); i++) {
			if (Objects[i].name == name) {
				Objects.erase(Objects.begin() + i);
				return;
			}
			Objects[i].Object->removeChild(name);
		}
	}
}

bool Scene::IsOfName(std::string name)
{
	for (auto& obj : Objects) {
		if (obj.name == name) {
			return true;
		}
	}
	return false;
}

Scene::~Scene()
{
}
