#include "SpriteComponent.h"


void SpriteComponent::setGeometry()
{
	float planeVerts[] = {
	-0.5f, -0.5f,  0.0f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.0f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.0f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.0f,  0.0f, 0.0f,
	};
	vertices.push_back(Vertex(glm::vec3(planeVerts[5 * 0 + 0], planeVerts[5 * 0 + 1], planeVerts[5 * 0 + 2]), glm::vec2(planeVerts[5 * 0 + 3], planeVerts[5 * 0 + 4])));
	vertices.push_back(Vertex(glm::vec3(planeVerts[5 * 1 + 0], planeVerts[5 * 1 + 1], planeVerts[5 * 1 + 2]), glm::vec2(planeVerts[5 * 1 + 3], planeVerts[5 * 1 + 4])));
	vertices.push_back(Vertex(glm::vec3(planeVerts[5 * 2 + 0], planeVerts[5 * 2 + 1], planeVerts[5 * 2 + 2]), glm::vec2(planeVerts[5 * 2 + 3], planeVerts[5 * 2 + 4])));
	vertices.push_back(Vertex(glm::vec3(planeVerts[5 * 3 + 0], planeVerts[5 * 3 + 1], planeVerts[5 * 3 + 2]), glm::vec2(planeVerts[5 * 3 + 3], planeVerts[5 * 3 + 4])));
	vertices.push_back(Vertex(glm::vec3(planeVerts[5 * 4 + 0], planeVerts[5 * 4 + 1], planeVerts[5 * 4 + 2]), glm::vec2(planeVerts[5 * 4 + 3], planeVerts[5 * 4 + 4])));
	vertices.push_back(Vertex(glm::vec3(planeVerts[5 * 5 + 0], planeVerts[5 * 5 + 1], planeVerts[5 * 5 + 2]), glm::vec2(planeVerts[5 * 5 + 3], planeVerts[5 * 5 + 4])));
	setupBuffers();
}

SpriteComponent::SpriteComponent() : DrawableComponent(nullptr)
{

	setGeometry();
}

SpriteComponent::SpriteComponent(GameObject * go) : DrawableComponent(go)
{
	RendererId = RendererManager::GetInstance()->AddRenderer<SpriteRenderer>();
	setGeometry();
}

void SpriteComponent::SetCameraFollowing(bool followCylindrically, bool AdditionalFollowingSphericaly)
{
	cameraFollowing = 0;
	if (followCylindrically) {
		cameraFollowing = 1;
		if (AdditionalFollowingSphericaly) {
			cameraFollowing += 2;
		}
	}
}

char SpriteComponent::GetCameraFollowing()
{
	return cameraFollowing;
}
