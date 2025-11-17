#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "../MeshBB.h"

using glm::fvec3;

/**
 * @brief Interface for GUI components in the application.
 */
class IGui
{
public:
	virtual ~IGui() = default;
	/// @brief Draws the GUI elements.
	virtual void drawGui() = 0;
	virtual fvec3 *getClearColorRef() = 0;
};
