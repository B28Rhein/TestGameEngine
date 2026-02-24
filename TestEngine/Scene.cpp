#include "Game.h"


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

Entry<GameObject> Scene::GetObjectByName(std::string name)
{
	std::queue<Entry<GameObject>> q;
	for (auto& ge : Objects) {
		q.push(ge);
	}
	do {
		if (q.front().name == name) {
			return q.front();
		}
		auto go = q.front().Object;
		q.pop();
		for (auto& c : go->getChildren()) {
			q.push(c);
		}
	} while (!q.empty());
	return Entry<GameObject>("notfound", nullptr);
}

std::vector<Entry<GameObject>>* Scene::GetObjects()
{
	return &Objects;
}

void Scene::RemoveObject(std::string name)
{
	if (GetObjectByName(name).Object != nullptr) {
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
