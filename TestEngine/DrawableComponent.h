#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/fwd.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>
#include <vector>
#include "Vertex.h"
#include "Component.h"
#include "Shader.h"

class DrawableComponent : public Component
{
private:
	unsigned int VAO, VBO, EBO;
public:
	int RendererId = -1;
	DrawableComponent();
	DrawableComponent(GameObject* go);
	unsigned int GetVAO();
	Shader* getShader();
	std::vector<Vertex>* GetVerices();
	void setShader(Shader* shader);
protected:
	Shader* shader;
	std::vector<Vertex> vertices;
	void setupBuffers();

};

