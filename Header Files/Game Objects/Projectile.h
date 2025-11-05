#pragma once
#include "ITemporaryGameObject.h"

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

class Projectile : public ITemporaryGameObject
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

	MeshBB *getMesh() const
	{
		return this->mesh;
	}

	void update(float deltaTime) override;
	void render(float currentTime) override;
	bool shouldDestroy() override;

private:
	MeshBB *mesh;
	float speed = 2500.0f;
	ivec2 windowSize;
};
