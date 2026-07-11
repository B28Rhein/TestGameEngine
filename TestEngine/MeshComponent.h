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
	unsigned int VAO, VBO, EBO;
public:
	MeshComponent();
	MeshComponent(GameObject* go);
	MeshComponent(Shader* _shader);
	void setMesh(float* verts);
	void setShader(Shader* shader);
	Shader* getShader();
	std::vector<Vertex>* GetVerices();
	unsigned int GetVAO();
	~MeshComponent();

protected:
	std::vector<Vertex> vertices;
	void setupBuffers();
	Shader* shader;
};

