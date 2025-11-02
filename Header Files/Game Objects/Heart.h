#pragma once

#include "IGameObject.h"

class Heart : public IGameObject
{
public:
	Heart(MeshBB *mesh);
	~Heart() override;

	void update(float deltaTime) override;
	void render(float currentTime) override;

private:
	MeshBB *mesh;
};
