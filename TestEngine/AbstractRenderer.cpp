#include "AbstractRenderer.h"

AbstractRenderer::AbstractRenderer(bool stbiFlipVert)
{
	stbi_set_flip_vertically_on_load(stbiFlipVert);
}



