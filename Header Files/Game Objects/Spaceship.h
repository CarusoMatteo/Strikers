#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "../Shape.h"

using glm::fvec3;
using glm::fvec4;
using glm::ivec2;
using std::string;
using std::vector;

class MeshBB;

class Spaceship : public IGameObject
{
public:
	Spaceship(
		string vertexName,
		string fragmentName,
		Shape shape,
		fvec3 position,
		fvec3 scaleVector,
		ivec2 windowSize);
	~Spaceship() override;

	void update(float deltaTime) override;
	void render(float currentTime) override;

private:
	MeshBB *mesh;
	float speed = 500.0f;
};
