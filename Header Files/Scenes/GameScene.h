#pragma once
#include "IScene.h"

#include <vector>
#include <utility>
#include <glm/glm.hpp>

using glm::fvec2;
using glm::fvec3;
using glm::ivec2;
using std::pair;
using std::vector;

class Background;
class Heart;
class Spaceship;
class Projectile;
class ProjectileExplosion;
class Enemy;
class EnemyExplosion;
class IGameObject;
class ITemporaryGameObject;
class IGui;

/**
 * @brief Represents the game scene.
 */
class GameScene : public IScene
{
public:
	GameScene(ivec2 windowSize, fvec3 *clearColorRef, bool *startGame);
	~GameScene();

	void updateGameObjects(float deltaTime);
	void renderScene(float currentTime);

	float getScore() const
	{
		return this->score;
	}

private:
	Background *background;
	/// @brief All persistent game objects in the scene.
	vector<IGameObject *> *gameObjects;
	/// @brief All temporary game objects in the scene.
	vector<ITemporaryGameObject *> *temporaryGameObjects;
	/// @brief The player's spaceship. It is also contained in gameObjects, but it is useful to have a separate reference.
	Spaceship *spaceship;

	IGui *gui;
	ivec2 windowSize;
	bool *startGame;
	float score = 0.0f;

	/**
	 * The time in between enemy spawn is random, chosen between these two values.
	 */
	const fvec2 enemySpawnIntervalRange = fvec2(0.5f, 2.5f);
	/// @brief The current interval for enemy spawning.
	float enemySpawnInterval = 1.0f;
	/// @brief Possible enemy spawn positions.
	vector<fvec3> enemySpawnPositions;
	/// @brief Time since the last enemy spawn.
	float timeSinceLastEnemySpawn = 0.0f;

	static Background *createBackground(ivec2 windowSize);
	static Heart *createHeart(ivec2 windowSize, float *spaceshipHealthRef);
	static Spaceship *createSpaceship(ivec2 windowSize);
	static Projectile *createProjectile(ivec2 windowSize, fvec3 spaceshipPosition);
	static ProjectileExplosion *createProjectileExplosion(ivec2 windowSize, fvec3 spawnPosition);
	static Enemy *createEnemy(ivec2 windowSize, vector<fvec3> enemySpawnPositions);
	static EnemyExplosion *createEnemyExplosion(ivec2 windowSize, fvec3 spawnPosition, fvec3 sizeWorld);

	void spawnProjectile();
	void spawnEnemy(float deltaTime);
	/// @brief Performs cleanup of temporary game objects that should be deleted.
	void deleteTemporaryGameObjects();
	void renderGameObjects(float currentTime);
	/// @brief Checks for collisions between game objects and handles them.
	void checkCollisions();

	/// @brief Substitutes an enemy at the given position with an enemyExplosion.
	/// @param position The position where to spawn the enemy explosion.
	void replaceEnemy(size_t position);
	/// @brief Substitutes a projectile at the given position with a projectileExplosion.
	/// @param position The position where to spawn the projectile explosion.
	void replaceProjectile(size_t position);
};