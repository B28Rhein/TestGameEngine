#include "TransformComponent.h"

TransformComponent::TransformComponent(GameObject* go) : Component(go)
{
}

glm::vec3 TransformComponent::GetPos()
{
    return position;
}

glm::vec3 TransformComponent::GetRot()
{
    return rotation;
}

glm::vec3 TransformComponent::GetScale()
{
    return scale;
}

void TransformComponent::SetPos(glm::vec3 nPos)
{
	auto children = gameObject->getChildren();
	for (auto& c : children) {
		auto TransComp = c.Object->GetComponent<TransformComponent>();
		glm::vec3 vec = TransComp->position - position;
		TransComp->position = position + vec;
	}
	position = nPos;
}

void TransformComponent::SetRot(glm::vec3 nRot)
{
	rotation = nRot;
}

void TransformComponent::SetScale(glm::vec3 nScale)
{
	scale = nScale;
}

void TransformComponent::SetTransform(glm::vec3 nPos, glm::vec3 nRot, glm::vec3 nScale)
{
	SetPos(nPos);
	SetRot(nRot);
	SetScale(nScale);
}

void TransformComponent::ChangePosBy(glm::vec3 addPos)
{
	glm::vec3 nPos = position + addPos;
	SetPos(nPos);
}

void TransformComponent::ChangeRotBy(glm::vec3 addRot)
{
	glm::vec3 nRot = rotation + addRot;
	SetRot(nRot);
}

void TransformComponent::ChangeScaleBy(glm::vec3 addScale)
{
	glm::vec3 nScale = scale + addScale;
	SetScale(nScale);
}
