#include "Renderer3D.h"

Renderer3D::Renderer3D(bool stbiFlipVert) : AbstractRenderer(stbiFlipVert)
{
}

void Renderer3D::setupCamera(std::string name, CameraMode CM)
{
	std::shared_ptr<Game> g = Game::GetInstance();
	std::pair<int, int> WindowSize = g->getWindowSize();
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	Camera* tmp = new Camera(1.5f, 0.1f, cameraPos, cameraFront, cameraUp, CM, WindowSize);
	SelectedCamera = tmp;
	g->GetCurrentScene()->Object->AddObject(std::shared_ptr<GameObject>(tmp), name);
}

void Renderer3D::Render()
{
	glClearColor(0.8f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glm::mat4 view = SelectedCamera->getLookAt();
	glm::mat4 projection = SelectedCamera->getPerspective();
	std::shared_ptr<Game> g = Game::GetInstance();
	auto objects = g->GetCurrentScene()->Object->GetObjects();
	for (auto& go : *objects) {
		go.Object->Draw(view, projection);
	}
}

void Renderer3D::SelectCameraByName(std::string name) {
	std::shared_ptr<Game> g = Game::GetInstance();
	Entry<GameObject> oe = g->GetCurrentScene()->Object->GetObjectByName(name);
	if (oe.Object != nullptr) {
		SelectedCamera = (AbstractCamera*)(Camera*)(oe.Object.get());
	}
}