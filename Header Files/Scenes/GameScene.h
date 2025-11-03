#pragma once
#include "Scene.h"

#include <vector>
#include <utility>
#include <glm/glm.hpp>

using glm::fvec3;
using glm::ivec2;
using std::pair;
using std::vector;

class Background;
class Heart;
class Spaceship;
class Projectile;
class IGameObject;
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
	vector<Projectile *> *projectiles;
	Spaceship *spaceship;

	IGui *gui;
	ivec2 windowSize;

	static Background *createBackground(ivec2 windowSize);
	static Heart *createHeart(ivec2 windowSize);
	static Spaceship *createSpaceship(ivec2 windowSize);
	static Projectile *createProjectile(ivec2 windowSize, fvec3 spaceshipPosition);

	void spawnProjectile();
	void deleteOffScreenProjectiles();
	void renderGameObjects(float currentTime);
	void renderGui();
};