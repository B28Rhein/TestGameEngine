#include "TextureComponent.h"

TextureComponent::TextureComponent(std::string texPath, glm::vec4 _TexMod) : Component(nullptr)
{
	texture = new Texture(texPath);
	TexMod = glm::vec4(1, 1, 1, 1);
}

TextureComponent::TextureComponent(GameObject * go) : Component(go)
{
	TexMod = glm::vec4(1, 1, 1, 1);
	texture = nullptr;
}

TextureComponent::TextureComponent() : Component(nullptr)
{
	TexMod = glm::vec4(1, 1, 1, 1);
	texture = nullptr;
}

void TextureComponent::AssignTexture(std::string texPath)
{
	if (texture != nullptr) {
		texture->~Texture();
	}
	texture = new Texture(texPath);
}

void TextureComponent::setTexMod(glm::vec3 Colour, float alpha)
{
	TexMod = glm::vec4(Colour, alpha);
}

glm::vec4 TextureComponent::getTexMod()
{
	return TexMod;
}

Texture* TextureComponent::getTexture()
{
	return texture;
}