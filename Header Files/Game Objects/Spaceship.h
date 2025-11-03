#pragma once

#include "IGameObject.h"

class MeshBB;

class Spaceship : public IGameObject
{
public:
	Spaceship();
	~Spaceship() override;

	void update(float deltaTime) override;
	void render(float currentTime) override;

private:
	MeshBB *mesh;
	float speed = 500.0f;
};
