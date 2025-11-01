#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "../Mesh.h"

using glm::vec4;

class IGameObject
{
public:
	virtual ~IGameObject() = default;

	virtual void update(float deltaTime) = 0;
	virtual void render(float currentTime) = 0;

protected:
	vec4 position;
	float rotationDegrees;
	bool isAlive;
	Mesh *mesh;

	virtual void buildShader() = 0;
};
