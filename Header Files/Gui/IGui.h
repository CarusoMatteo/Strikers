#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "../MeshBB.h"

class IGui
{
public:
	virtual ~IGui() = default;
	virtual void drawGui() = 0;
};
