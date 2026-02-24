#pragma once
#include <GLFW/glfw3.h>
#include <memory>
#include "Window.h"
#include "GameObject.h"
#include "Camera.h"

class AbstractRenderer
{
protected:
	AbstractCamera* SelectedCamera;
public:
	AbstractRenderer(bool stbiFlipVert);
	virtual void setupCamera(std::string name, CameraMode CM) = 0;
	virtual void SelectCameraByName(std::string name) = 0;
	virtual void Render() = 0;
	AbstractCamera* getSelectedCamera();
};

