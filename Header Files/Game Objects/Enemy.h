#pragma once
#include "ITemporaryGameObject.h"

#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "../Shape.h"
#include "../Parameters.h"

using glm::fvec3;
using glm::fvec4;
using glm::ivec2;
using std::string;
using std::vector;

class MeshBB;

class Enemy : public ITemporaryGameObject
{
public:
	Enemy(
		string vertexName,
		string fragmentName,
		Shape shape,
		fvec3 position,
		fvec3 scaleVector,
		ivec2 windowSize);
	~Enemy() override;

	MeshBB *getMesh() const
	{
		return this->mesh;
	}

	fvec3 getSizeWorld() const;

	void update(float deltaTime) override;
	void render(float currentTime) override;

	bool shouldDelete() override;

private:
	MeshBB *mesh;
	float speed = Parameters::enemySpeed;
	ivec2 windowSize;
};
