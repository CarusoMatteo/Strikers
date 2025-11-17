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

class MeshCurveBB;

/**
 * @brief Represents the player's spaceship gameObject in the game.
 */
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
	/**
	 * @brief Calculates the projectile spawn position based on the spaceship's current position and orientation.
	 */
	fvec3 getProjectileSpawnPosition() const;
	MeshCurveBB *getMesh() const
	{
		return this->mesh;
	}
	bool isAlive() const
	{
		return this->health > 0.0f;
	}
	float *getHealthRef()
	{
		return &this->health;
	}

	void update(float deltaTime) override;
	void render(float currentTime) override;

	void takeDamage(int amount = 1);

private:
	const float maxHealth = Parameters::spaceshipMaxHealth;
	const float speed = Parameters::spaceshipSpeed;
	const float invincibilityTime = Parameters::spaceshipIvincibilityTime;
	const int invincibleBlinkFrequencyHz = Parameters::spaceshipInvincibleBlinkFrequencyHz;

	MeshCurveBB *mesh;
	ivec2 windowSize;
	float health = maxHealth;
	bool isInvincible = false;
	float invincibilityTimer = 0.0f;

	bool isVisible() const;
};
