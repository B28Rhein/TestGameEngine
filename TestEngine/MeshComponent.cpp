#include "MeshComponent.h"




MeshComponent::MeshComponent() : DrawableComponent(nullptr)
{
	shader = nullptr;
}

MeshComponent::MeshComponent(GameObject* go) : DrawableComponent(go)
{
	shader = nullptr;
	RendererId = RendererManager::GetInstance()->AddRenderer<Renderer3D>();
}

MeshComponent::MeshComponent(Shader* _shader) : DrawableComponent(nullptr){
	shader = _shader;
}





void MeshComponent::setMesh(float* verts)
{
	for (int i = 0; i < 36; i++) {
		vertices.push_back(Vertex(glm::vec3(verts[5 * i + 0], verts[5 * i + 1], verts[5 * i + 2]), glm::vec2(verts[5 * i + 3], verts[5 * i + 4])));
	}
	setupBuffers();
}








MeshComponent::~MeshComponent()
{
}
