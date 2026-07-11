#include "DrawableComponent.h"

DrawableComponent::DrawableComponent() : Component(nullptr)
{}

DrawableComponent::DrawableComponent(GameObject * go) : Component(go)
{}
