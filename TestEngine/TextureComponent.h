#pragma once
#include "Component.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>
#include "Texture.h"
class TextureComponent :
    public Component
{
    glm::vec4 TexMod;
public:
    TextureComponent(std::string texPath, glm::vec4 _TexMod = glm::vec4(1, 1, 1, 1));
    TextureComponent(GameObject* go);
    TextureComponent();
    void AssignTexture(std::string texPath);
    void setTexMod(glm::vec3 Colour, float alpha);
    glm::vec4 getTexMod();
    Texture* getTexture();

protected:
    Texture* texture;
};

