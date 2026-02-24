#include "Renderer2D.h"

Renderer2D::Renderer2D(bool stbiFlipVert) : AbstractRenderer(stbiFlipVert)
{
}

void Renderer2D::setupCamera(std::string name, CameraMode CM)
{
	std::shared_ptr<Game> g = Game::GetInstance();
	std::pair<int, int> WindowSize = g->getWindowSize();
	glm::vec2 cameraPos = glm::vec2(0.0f, 0.0f);
	Camera2D* tmp = new Camera2D(1.5f, 0.1f, cameraPos, WindowSize, CM);
	SelectedCamera = tmp;
	g->GetCurrentScene()->Object->AddObject(std::shared_ptr<GameObject>(tmp), name);
}

void Renderer2D::Render()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 view = SelectedCamera->getLookAt();
	glm::mat4 projection = SelectedCamera->getPerspective();
	std::shared_ptr<Game> g = Game::GetInstance();
	auto objects = g->GetCurrentScene()->Object->GetObjects();
	for (auto& go : *objects) {
		go.Object->Draw(view, projection);
	}
}

void Renderer2D::SelectCameraByName(std::string name)
{
	std::shared_ptr<Game> g = Game::GetInstance();
	Entry<GameObject> oe = g->GetCurrentScene()->Object->GetObjectByName(name);
	if (oe.Object != nullptr) {
		SelectedCamera = (AbstractCamera*)(Camera2D*)(oe.Object.get());
	}
}

