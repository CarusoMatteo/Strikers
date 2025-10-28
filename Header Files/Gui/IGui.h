#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "../Mesh.h"

using glm::vec4;

class IGui
{
public:
	virtual ~IGui() = default;

	virtual void drawGui() = 0;
};
