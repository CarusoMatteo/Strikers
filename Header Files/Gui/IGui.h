#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "../MeshBB.h"

using glm::vec4;

class IGui
{
public:
	virtual void drawGui() = 0;
};
