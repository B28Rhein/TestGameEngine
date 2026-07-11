#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/fwd.hpp>
#include <vector>

#include "Texture.h"
#include "Vertex.h"
#include "DrawableComponent.h"
#include "Shader.h"
#include "GameObject.h"
#include "RendererManager.h"
#include "Renderer3D.h"

enum verticesSetupMode
{
	TestCube,
	Custom,
};

class MeshComponent : public DrawableComponent
{

public:
	MeshComponent();
	MeshComponent(GameObject* go);
	MeshComponent(Shader* _shader);
	void setMesh(float* verts);
	~MeshComponent();

protected:
	
	

};

