#pragma once
#include "glm/glm.hpp"

struct Vertex {
	glm::vec3 Position;
	glm::vec2 TexCoords;
	Vertex(glm::vec3 pos, glm::vec2 texPos) {
		Position = pos;
		TexCoords = texPos;
	}
};

