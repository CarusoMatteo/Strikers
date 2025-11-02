#pragma once

#include "IGameObject.h"
#include <glm/glm.hpp>

using glm::fvec3;

class Heart : public IGameObject
{
public:
	Heart(fvec3 position, MeshBB *mesh);
	~Heart() override;

	void update(float deltaTime) override;
	void render(float currentTime) override;

private:
	fvec3 position;
	MeshBB *mesh;
};
