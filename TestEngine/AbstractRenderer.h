#pragma once
#include <GLFW/glfw3.h>
#include <memory>
#include "Window.h"
#include "GameObject.h"
#include <algorithm>


class AbstractRenderer
{
protected:
public:
	AbstractRenderer(bool stbiFlipVert);
	virtual void Render() = 0;
};

