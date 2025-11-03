#pragma once
#include "IGameObject.h"

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

class Projectile : public IGameObject
{
public:
	Projectile(
		string vertexName,
		string fragmentName,
		Shape shape,
		fvec3 position,
		fvec3 scaleVector,
		ivec2 windowSize);
	~Projectile() override;

	void update(float deltaTime) override;
	void render(float currentTime) override;
	bool isOffScreen();

private:
	MeshBB *mesh;
	float speed = 2500.0f;
	ivec2 windowSize;
};
