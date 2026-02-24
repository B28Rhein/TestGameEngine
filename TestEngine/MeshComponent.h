#pragma once
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
	glm::mat4 getModel(glm::vec3 pos);
public:
	MeshComponent();
	MeshComponent(GameObject* go);
	MeshComponent(Shader* _shader, std::string texPath, glm::vec4 _TexMod = glm::vec4(1, 1, 1, 1));
	void AssignTexture(std::string texPath);
	void setScale(glm::vec3 nScale);
	void setTexMod(glm::vec3 Colour, float alpha);
	void setMesh(float* verts);
	void setShader(Shader* shader);
	virtual void Draw(glm::mat4 view, glm::mat4 projection, glm::vec3 pos);
	~MeshComponent();

protected:
	std::vector<Vertex> vertices;
	Texture* texture;
	void setupBuffers();
	Shader* shader;
	glm::vec3 scale;
};

