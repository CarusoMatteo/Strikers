#pragma once
#include "IGameObject.h"

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

	fvec3 getPosition() const;
	fvec3 getProjectileSpawnPosition() const;
	MeshBB *getMesh() const
	{
		return this->mesh;
	}

	void update(float deltaTime) override;
	void render(float currentTime) override;
	void takeDamage(int amount = 1);

private:
	const float invincibilityTime = Parameters::spaceshipIvincibilityTime;
	const int invincibleBlinkFrequencyHz = Parameters::spaceshipInvincibleBlinkFrequencyHz;
	const float speed = Parameters::spaceshipSpeed;

	MeshBB *mesh;
	bool isInvincible = false;
	float invincibilityTimer = 0.0f;

	bool isVisible();
};
