#pragma once

#include "../Mesh.h"

class IGameObject
{
public:
	virtual ~IGameObject() = default;

	virtual void update(float deltaTime) = 0;
	virtual void render(float currentTime) = 0;
};
