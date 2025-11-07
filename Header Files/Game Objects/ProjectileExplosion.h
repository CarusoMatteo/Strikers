#pragma once
#include "ITemporaryGameObject.h"

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include "../Shape.h"
#include "../Parameters.h"

using glm::fvec3;
using glm::fvec4;
using glm::ivec2;
using std::string;
using std::vector;

class Mesh;

class ProjectileExplosion : public ITemporaryGameObject
{
public:
	ProjectileExplosion(
		string vertexName,
		string fragmentName,
		Shape shape,
		fvec3 position,
		fvec3 scaleVector,
		ivec2 windowSize);
	~ProjectileExplosion() override;

	Mesh *getMesh() const
	{
		return this->mesh;
	}

	void update(float deltaTime) override;
	void render(float currentTime) override;
	bool shouldDelete() override;

private:
	const float timeToLiveSeconds = Parameters::explosionTimeToLiveSeconds;
	float creationTime;

	Mesh *mesh;
	ivec2 windowSize;
};
