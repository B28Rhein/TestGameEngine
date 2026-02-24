#pragma once
#include "Window.h"
#include <vector>
#include "GameObject.h"
#include "Camera.h"
#include "Camera2D.h"
#include "Game.h"
#include "AbstractRenderer.h"

class Renderer2D : public AbstractRenderer
{
public:
	Renderer2D(bool stbiFlipVert);
	void setupCamera(std::string name, CameraMode CM = CameraMode::Camera2DOrtho) override;
	void Render() override;
	void SelectCameraByName(std::string name) override;
	~Renderer2D();
};

