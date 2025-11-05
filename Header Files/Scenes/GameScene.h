#pragma once
#include "Scene.h"

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
class Enemy;
class IGameObject;
class ITemporaryGameObject;
class IGui;

class GameScene : public Scene
{
public:
	GameScene(ivec2 windowSize, fvec3 *clearColorRef);
	~GameScene();

	void updateGameObjects(float deltaTime);
	void renderScene(float currentTime);

private:
	Background *background;
	vector<IGameObject *> *gameObjects;
	vector<ITemporaryGameObject *> *temporaryGameObjects;
	Spaceship *spaceship;

	IGui *gui;
	ivec2 windowSize;

	const fvec2 enemySpawnIntervalRange = fvec2(0.5f, 2.5f);
	float enemySpawnInterval = 1.0f;
	vector<fvec3> enemySpawnPositions;
	float timeSinceLastEnemySpawn = 0.0f;

	static Background *createBackground(ivec2 windowSize);
	static Heart *createHeart(ivec2 windowSize);
	static Spaceship *createSpaceship(ivec2 windowSize);
	static Projectile *createProjectile(ivec2 windowSize, fvec3 spaceshipPosition);
	static Enemy *createEnemy(ivec2 windowSize, vector<fvec3> enemySpawnPositions);

	void spawnProjectile();
	void spawnEnemy(float deltaTime);
	void destroyTemporaryGameObjects();
	void renderGameObjects(float currentTime);
	void renderGui();
};