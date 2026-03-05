#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/fwd.hpp>
#include <vector>

#include "Texture.h"
#include "Vertex.h"
#include "Component.h"
#include "Shader.h"
#include "GameObject.h"

enum verticesSetupMode
{
	TestCube,
	Custom,
};

class MeshComponent : public Component
{
	unsigned int VAO, VBO, EBO;
	glm::vec4 TexMod;
public:
	MeshComponent();
	MeshComponent(GameObject* go);
	MeshComponent(Shader* _shader, std::string texPath, glm::vec4 _TexMod = glm::vec4(1, 1, 1, 1));
	void AssignTexture(std::string texPath);
	void setTexMod(glm::vec3 Colour, float alpha);
	glm::vec4 getTexMod();
	void setMesh(float* verts);
	void setShader(Shader* shader);
	Shader* getShader();
	Texture* getTexture();
	std::vector<Vertex>* GetVerices();
	unsigned int GetVAO();
	~MeshComponent();

protected:
	std::vector<Vertex> vertices;
	Texture* texture;
	void setupBuffers();
	Shader* shader;
};

