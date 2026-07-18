#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(bool stbiFlipVert) : AbstractRenderer(stbiFlipVert)
{}

void SpriteRenderer::Render(GameObject* go, glm::mat4 view, glm::mat4 projection)
{
	DrawableComponent* mc = go->GetComponent<SpriteComponent>();
	TextureComponent* tc = go->GetComponent<TextureComponent>();
	glm::vec4 texMod = tc != nullptr ? tc->getTexMod() : glm::vec4(1, 1, 1, 1);
	Shader* shader = mc->getShader();
	shader->use();
	glm::mat4 model = GetObjectsModel(go);

	shader->setMat4("projection", projection);
	shader->setMat4("view", view);
	shader->setMat4("model", model);

	shader->setVec4("FragMod", texMod);

	if (tc == nullptr || tc->getTexture() == nullptr) {
		shader->setInt("texAssigned", -1);
	}
	else
	{
		shader->setInt("texAssigned", 0);
	}

	glActiveTexture(GL_TEXTURE0);
	shader->setInt("tex", 0);
	glBindTexture(GL_TEXTURE_2D,
		tc != nullptr ? tc->getTexture()->ID : -1
	);

	glBindVertexArray(mc->GetVAO());
	glDrawArrays(GL_TRIANGLES, 0, mc->GetVerices()->size());
}

glm::mat4 SpriteRenderer::GetObjectsModel(GameObject * go)
{
	TransformComponent* tc = go->GetComponent<TransformComponent>();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, tc->GetPos());
	glm::vec3 radianRot = tc->GetRot();
	char cf = go->GetComponent<SpriteComponent>()->GetCameraFollowing();
	if (cf % 2 == 1) {
		auto ctc = Game::GetInstance()->getSelectedCamera()->GetComponent<TransformComponent>();
		auto dir = ctc->GetPos() - tc->GetPos();
		dir.y = 0;
		dir = glm::normalize(dir);
		auto angleCos = glm::dot(glm::vec3(0.0f, 0.0f, 1.0f), dir);
		auto upAux = glm::cross(glm::vec3(0.0f, 0.0f, 1.0f), dir);
		model = glm::rotate(model, acos(angleCos), upAux);
		if ((cf >> 1) % 2 == 1) {
			dir = ctc->GetPos() - tc->GetPos();
			dir = glm::normalize(dir);
			angleCos = glm::dot(glm::vec3(dir.x, 0.0f, dir.z), dir);
			model = glm::rotate(model, acos(angleCos), dir.y < 0 ? glm::vec3(1, 0, 0) : glm::vec3(-1, 0, 0));
		}
	}

	if (cf == 0) {
		glm::quat quaternion = glm::quat(radianRot);
		glm::mat4 rotMat = glm::toMat4(quaternion);
		model = model * rotMat;
	}
	

	model = glm::scale(model, tc->GetScale());
	return model;
}
