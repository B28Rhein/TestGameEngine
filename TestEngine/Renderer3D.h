#pragma once
#include "Window.h"
#include <vector>
#include "GameObject.h"
#include "Camera.h"
#include "Camera2D.h"
#include "Game.h"
#include "AbstractRenderer.h"

class Renderer3D : public AbstractRenderer
{
public:
	Renderer3D(bool stbiFlipVert);
	void setupCamera(std::string name, CameraMode CM = CameraMode::fps3DCamera) override;
	void Render() override;
	void SelectCameraByName(std::string name) override;
};

