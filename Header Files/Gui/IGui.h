#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "../Mesh.h"

using glm::vec4;

class IGui
{
public:
	virtual void drawGui() = 0;
};
