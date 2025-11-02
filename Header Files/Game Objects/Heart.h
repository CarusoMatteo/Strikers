#pragma once

#include "IGameObject.h"

class Heart : IGameObject
{
	Heart(MeshBB *mesh);
	~Heart() override;

	void update(float deltaTime) override;
	void render(float currentTime) override;

private:
	MeshBB *mesh;
};
