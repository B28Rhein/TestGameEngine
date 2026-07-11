#pragma once
#include "DrawableComponent.h"
#include "SpriteRenderer.h"
#include "RendererManager.h"
class SpriteComponent :
    public DrawableComponent
{
public:
    void setGeometry();
    SpriteComponent();
    SpriteComponent(GameObject* go);
};

