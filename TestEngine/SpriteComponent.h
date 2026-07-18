#pragma once
#include "DrawableComponent.h"
#include "SpriteRenderer.h"
#include "RendererManager.h"
class SpriteComponent :
    public DrawableComponent
{
    char cameraFollowing;
public:
    void setGeometry();
    SpriteComponent();
    SpriteComponent(GameObject* go);
    void SetCameraFollowing(bool followCylindrically, bool AdditionalFollowingSphericaly);
    char GetCameraFollowing();
};

