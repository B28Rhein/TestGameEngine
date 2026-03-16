#include "Renderer3D.h"

Renderer3D::Renderer3D(bool stbiFlipVert) : AbstractRenderer(stbiFlipVert)
{
}

void Renderer3D::Render()
{
	glClearColor(0.8f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

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
	auto objects = g->GetGameObjectsWithComponent<MeshComponent>();
	auto predicate = [](GameObject* a, GameObject* b) {
		float aAlpha = a->GetComponent<MeshComponent>()->getTexMod().a;
		float bAlpha = b->GetComponent<MeshComponent>()->getTexMod().a;
		if (aAlpha != bAlpha) {
			return aAlpha > bAlpha ;
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
	for (auto go : objects) {
		MeshComponent* mc = go->GetComponent<MeshComponent>();
		Shader* shader = mc->getShader();
		shader->use();
		glm::mat4 model = GetObjectsModel(go);

		shader->setMat4("projection", projection);
		shader->setMat4("view", view);
		shader->setMat4("model", model);

		shader->setVec4("FragMod", mc->getTexMod());

		glActiveTexture(GL_TEXTURE0);
		shader->setInt("tex", 0);
		glBindTexture(GL_TEXTURE_2D, mc->getTexture()->ID);

		glBindVertexArray(mc->GetVAO());
		glDrawArrays(GL_TRIANGLES, 0, mc->GetVerices()->size());
	}
}

glm::mat4 Renderer3D::GetObjectsModel(GameObject* go)
{
	TransformComponent* tc = go->GetComponent<TransformComponent>();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, tc->GetPos());
	glm::vec3 radianRot = tc->GetRot();
	radianRot = glm::radians(radianRot);
	glm::quat quaternion = glm::quat(radianRot);
	glm::mat4 rotMat = glm::toMat4(quaternion);
	model = model * rotMat;
	model = glm::scale(model, tc->GetScale());
	return model;
}
