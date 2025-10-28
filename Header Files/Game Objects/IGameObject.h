#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "../Mesh.h"

using glm::vec4;

class IGameObject
{
public:
	virtual ~IGameObject() = default;

	virtual void render(double currentTime, double deltaTime) = 0;

protected:
	vec4 position;
	bool isAlive;
	Mesh *mesh;

	virtual void buildShader() = 0;
	virtual void update() = 0;
};
