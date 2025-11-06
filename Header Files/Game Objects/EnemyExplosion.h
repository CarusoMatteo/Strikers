#pragma once
#include "ITemporaryGameObject.h"

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include "../Shape.h"

using glm::fvec3;
using glm::fvec4;
using glm::ivec2;
using std::string;
using std::vector;

class Mesh;

class EnemyExplosion : public ITemporaryGameObject
{
public:
	EnemyExplosion(
		string vertexName,
		string fragmentName,
		Shape shapeHalf,
		fvec3 positionTop,
		fvec3 positionBottom,
		fvec3 scaleVector,
		ivec2 windowSize);
	~EnemyExplosion() override;

	void update(float deltaTime) override;
	void render(float currentTime) override;
	bool shouldDelete() override;

private:
	const float timeToLiveSeconds = 0.5f;
	float creationTime;

	const float maxHorizontalSpeed = 1000.0f;
	const float maxVerticalSpeed = 50.0f;

	Mesh *meshTop;
	Mesh *meshBottom;
	ivec2 windowSize;
};
