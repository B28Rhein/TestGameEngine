#include "MeshComponent.h"


MeshComponent::MeshComponent() : Component(nullptr)
{
	texture = nullptr;
	shader = nullptr;
	TexMod = glm::vec4(1, 1, 1, 1);
}

MeshComponent::MeshComponent(GameObject* go) : Component(go)
{
	texture = nullptr;
	shader = nullptr;
	TexMod = glm::vec4(1, 1, 1, 1);
}

MeshComponent::MeshComponent(Shader* _shader, std::string texPath, glm::vec4 _TexMod) : Component(nullptr){
	texture = new Texture(texPath);
	shader = _shader;
	TexMod = _TexMod;
}


void MeshComponent::setupBuffers()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
}

void MeshComponent::AssignTexture(std::string texPath)
{
	if (texture != nullptr) {
		texture->~Texture();
	}
	texture = new Texture(texPath);
}

void MeshComponent::setTexMod(glm::vec3 Colour, float alpha)
{
	TexMod = glm::vec4(Colour, alpha);
}

glm::vec4 MeshComponent::getTexMod()
{
	return TexMod;
}

void MeshComponent::setMesh(float* verts)
{
	for (int i = 0; i < 36; i++) {
		vertices.push_back(Vertex(glm::vec3(verts[5 * i + 0], verts[5 * i + 1], verts[5 * i + 2]), glm::vec2(verts[5 * i + 3], verts[5 * i + 4])));
	}
	setupBuffers();
}

void MeshComponent::setShader(Shader* shader)
{
	this->shader = shader;
}

Shader* MeshComponent::getShader()
{
	return shader;
}

Texture* MeshComponent::getTexture()
{
	return texture;
}

std::vector<Vertex>* MeshComponent::GetVerices()
{
	return &vertices;
}

unsigned int MeshComponent::GetVAO()
{
	return VAO;
}

MeshComponent::~MeshComponent()
{
}
