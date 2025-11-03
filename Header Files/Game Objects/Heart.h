#pragma once

#include "IGameObject.h"

#include <glm/glm.hpp>

using glm::fvec3;
class MeshBB;

class Heart : public IGameObject
{
public:
	Heart();
	~Heart() override;

	void update(float deltaTime) override;
	void render(float currentTime) override;

private:
	MeshBB *mesh;
};
