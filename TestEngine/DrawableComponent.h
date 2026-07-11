#pragma once
#include "Component.h"
class DrawableComponent : public Component
{
public:
	int RendererId;
	DrawableComponent();
	DrawableComponent(GameObject* go);
};

