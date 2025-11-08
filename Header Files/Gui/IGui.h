#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "../MeshBB.h"

using glm::fvec3;

class IGui
{
public:
	virtual ~IGui() = default;
	virtual void drawGui() = 0;
	virtual fvec3 *getClearColorRef() = 0;
};
