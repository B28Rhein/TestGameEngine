#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include "Texture.h"
#include "Shader.h"
#include <vector>
#include "Entry.h"
#include "Component.h"
#include "MeshComponent.h"
#include "TransformComponent.h"


class GameObject
{
	GameObject* parent;
public:
	GameObject(float xpos, float ypos, float zpos);
	GameObject(glm::vec3 nPos);
	void addChild(std::shared_ptr<GameObject> obj, std::string name);
	void removeChild(std::string name);
	std::vector<Entry<GameObject>> getChildren();
	GameObject* getParent();
	virtual ~GameObject();
	bool IsOfName(std::string name);

	template<class T>
	T* GetComponent() {
		for (auto c : components) {
			if (typeid(*c).name() == typeid(T).name()) {
				return (std::dynamic_pointer_cast<T>(c)).get();
			}
		}
		return nullptr;
	};

	template<class T>
	void AddComponent() {
		if (GetComponent<T>() == nullptr) {
			components.push_back(std::make_shared<T>(this));
		}
		else {
			std::cout << "Component of this type is already present\n";
		}
	}

protected:
	std::vector<Entry<GameObject>> children;
	std::vector<std::shared_ptr<Component>> components;
};

