#include "RendererManager.h"

std::unique_ptr<RendererManager> RendererManager::Instance = nullptr;

RendererManager::RendererManager()
{
	renderers = std::unordered_map<int, std::shared_ptr<AbstractRenderer>>();
}

RendererManager* RendererManager::GetInstance()
{
	if (Instance == nullptr) {
		Instance = std::make_unique<RendererManager>();
	}
	return RendererManager::Instance.get();
}

void RendererManager::Render()
{
	Game* g = Game::GetInstance();
	GameObject* sCamera = g->getSelectedCamera();
	CameraComponent* cc = sCamera->GetComponent<CameraComponent>();
	TransformComponent* tc = sCamera->GetComponent<TransformComponent>();
	glm::vec3 cameraPos = tc->GetPos();
	glm::vec3 cameraFront = cc->getFront();
	glm::vec3 cameraUp = cc->getUpVector();
	glm::vec3 cameraOffset = cc->getOffset();
	cameraPos += -glm::abs(cameraOffset.z) * cameraFront + cameraUp * cameraOffset.y + glm::cross(cameraFront, cameraUp) * cameraOffset.x;
	system("cls");
	std::cout << glm::to_string(cameraPos) << " " << glm::to_string(tc->GetPos());
	float cameraFov = cc->getFov();
	glm::mat4 projection;
	glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	if (cc->getType() == CameraProjectionType::perspective)
		projection = glm::perspective(cameraFov, (float)g->getWindowSize().first / (float)g->getWindowSize().second, 0.1f, 100.0f);
	else if (cc->getType() == CameraProjectionType::ortho)
		projection = glm::ortho(-((float)g->getWindowSize().first) / 2, ((float)g->getWindowSize().first) / 2, -((float)g->getWindowSize().second) / 2, ((float)g->getWindowSize().second) / 2);
	auto objects = g->GetGameObjectsWithComponent<DrawableComponent>();
	auto predicate = [](GameObject* a, GameObject* b) {

		float aAlpha = a->GetComponent<TextureComponent>() != nullptr ? a->GetComponent<TextureComponent>()->getTexMod().a : 1;
		float bAlpha = b->GetComponent<TextureComponent>() != nullptr ? b->GetComponent<TextureComponent>()->getTexMod().a : 1;
		if (aAlpha != bAlpha) {
			return aAlpha > bAlpha;
		}
		else {
			glm::vec3 cameraPos = Game::GetInstance()->getSelectedCamera()->GetComponent<TransformComponent>()->GetPos();
			glm::vec3 aPos = a->GetComponent<TransformComponent>()->GetPos();
			glm::vec3 bPos = b->GetComponent<TransformComponent>()->GetPos();
			float aLen = glm::length(aPos - cameraPos);
			float bLen = glm::length(bPos - cameraPos);
			return aLen > bLen;
		}

		};
	std::stable_sort(objects.begin(), objects.end(), predicate);
	for (auto o : objects) {
		int r = o->GetComponent<DrawableComponent>()->RendererId;
		//renderers[r]->Render(o, view, projection);
	}
}
