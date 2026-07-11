#pragma once
#include "AbstractRenderer.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "TextureComponent.h"
#include <unordered_map>

class RendererManager
{
private:
	std::unordered_map<int, std::shared_ptr<AbstractRenderer>> renderers;
	int nextRendererNr = 1;
	static std::unique_ptr<RendererManager> Instance;
	//for future
	//std::vector<RenderRule> renderRules;
public:
	RendererManager();
	static RendererManager* GetInstance();
	void Render();
	template<class T>
	T* GetRenderer() {
		for (auto r : renderers) {
			if (typeid(*(r.second)).name() == typeid(T).name()) {
				return (std::dynamic_pointer_cast<T>((r.second))).get();
			}
		}
		return nullptr;
	}
	template<class T>
	int AddRenderer() {
		if (GetRenderer<T>() == nullptr) {
			renderers.insert_or_assign(nextRendererNr, std::make_shared<T>(true));
			nextRendererNr++;
		}
		return nextRendererNr - 1;
	};
};

