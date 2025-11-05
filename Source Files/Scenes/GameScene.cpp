#include "../../Header Files/Scenes/GameScene.h"

#include "../../Header Files/Game Objects/Background.h"
#include "../../Header Files/Game Objects/Heart.h"
#include "../../Header Files/Game Objects/Spaceship.h"
#include "../../Header Files/Game Objects/Projectile.h"
#include "../../Header Files/Game Objects/Enemy.h"
#include "../../Header Files/Gui/MenuGui.h"
#include "../../Header Files/ShapeMaker.h"
#include "../../Header Files/InputEvents.h"
#include "../../Header Files/Random.h"

#include <iostream>
using namespace std;

GameScene::GameScene(ivec2 windowSize, fvec3 *clearColorRef) : windowSize(windowSize)
{
	this->background = GameScene::createBackground(this->windowSize);
	Heart *heart = GameScene::createHeart(this->windowSize);
	this->spaceship = GameScene::createSpaceship(this->windowSize);

	this->gameObjects = new vector<IGameObject *>{
		heart,
		spaceship};
	this->temporaryGameObjects = new vector<ITemporaryGameObject *>();

	this->gui = new MenuGui(clearColorRef);

	this->enemySpawnPositions = {
		fvec3(windowSize.x * 1.1f, windowSize.y * 0.2f, 0.0f),
		fvec3(windowSize.x * 1.1f, windowSize.y * 0.4f, 0.0f),
		fvec3(windowSize.x * 1.1f, windowSize.y * 0.6f, 0.0f),
		fvec3(windowSize.x * 1.1f, windowSize.y * 0.8f, 0.0f)};
}

#pragma region Game Object Creators

Background *GameScene::createBackground(ivec2 windowSize)
{
	string vertex = ".\\Shader Files\\Default\\DefaultVertex.glsl";
	string fragment = ".\\Shader Files\\Default\\DefaultFragment.glsl";

	fvec3 position = fvec3(0, 0, 0);
	fvec3 scaleVector = fvec3(windowSize, 1);

	fvec4 colorBottomLeft = fvec4(0.06f, 0.04f, 0.12f, 1);
	fvec4 colorBottomRight = fvec4(0.06f, 0.04f, 0.12f, 1);
	fvec4 colorTopLeft = fvec4(0.06f, 0.04f, 0.12f, 1);
	fvec4 colorTopRight = fvec4(0.06f, 0.04f, 0.12f, 1);

	Shape shapeData = ShapeMaker::makeBackgroundPlane(
		colorBottomLeft,
		colorBottomRight,
		colorTopLeft,
		colorTopRight);

	return new Background(
		vertex,
		fragment,
		shapeData,
		position,
		scaleVector,
		windowSize);
}

Heart *GameScene::createHeart(ivec2 windowSize)
{
	string vertex = ".\\Shader Files\\Heart\\HeartVertex.glsl";
	string fragment = ".\\Shader Files\\Heart\\HeartFragment.glsl";

	int numberOfTriangles = 100;
	fvec2 radius = fvec2(1, 1);

	fvec3 position = fvec3(windowSize.x * 0.1, windowSize.y / 3.0, 0.0);
	fvec3 scaleVector = fvec3(5, 5, 1);

	fvec4 colorCenter = fvec4(1, 0, 0, 1);
	fvec4 colorBorder = fvec4(0.5f, 0, 0, 1);

	Shape shapeData = ShapeMaker::makeHeart(
		numberOfTriangles,
		radius,
		colorCenter,
		colorBorder,
		false);

	return new Heart(
		vertex,
		fragment,
		shapeData,
		position,
		scaleVector,
		windowSize);
}

Spaceship *GameScene::createSpaceship(ivec2 windowSize)
{
	string vertex = ".\\Shader Files\\Default\\DefaultVertex.glsl";
	string fragment = ".\\Shader Files\\Default\\DefaultFragment.glsl";

	float width = 1;
	float height = 1;

	fvec3 position = fvec3(windowSize.x * 0.1, windowSize.y / 3.0, 0.0);
	fvec3 scaleVector = fvec3(100, 100, 1);

	fvec4 colorBottomLeft = fvec4(1);
	fvec4 colorBottomRight = fvec4(1);
	fvec4 colorTopLeft = fvec4(1);
	fvec4 colorTopRight = fvec4(1);

	Shape shapeData = ShapeMaker::makeRectangle(
		width,
		height,
		colorBottomLeft,
		colorBottomRight,
		colorTopLeft,
		colorTopRight);

	return new Spaceship(
		vertex,
		fragment,
		shapeData,
		position,
		scaleVector,
		windowSize);
}

Projectile *GameScene::createProjectile(ivec2 windowSize, fvec3 spaceshipPosition)
{
	string vertex = ".\\Shader Files\\Projectile\\ProjectileVertex.glsl";
	string fragment = ".\\Shader Files\\Projectile\\ProjectileFragment.glsl";

	float sideLenght = 1;

	fvec3 position = spaceshipPosition;
	fvec3 scaleVector = fvec3(50, 50, 1);

	fvec4 colorTop = fvec4(1, 1, 1, 1);
	fvec4 colorBottomLeft = fvec4(1, 1, 1, 1);
	fvec4 colorBottomRight = fvec4(1, 1, 1, 1);

	Shape shapeData = ShapeMaker::makeTriangle(
		sideLenght,
		colorTop,
		colorBottomLeft,
		colorBottomRight);

	return new Projectile(
		vertex,
		fragment,
		shapeData,
		position,
		scaleVector,
		windowSize);
}

Enemy *GameScene::createEnemy(ivec2 windowSize, vector<fvec3> enemySpawnPositions)
{
	string vertex = ".\\Shader Files\\Default\\DefaultVertex.glsl";
	string fragment = ".\\Shader Files\\Default\\DefaultFragment.glsl";

	float width = 1;
	float height = 1;

	fvec3 position = enemySpawnPositions[Random::getRandomInt(0, enemySpawnPositions.size())];
	fvec3 scaleVector = fvec3(50, 50, 1);

	fvec4 colorBottomLeft = fvec4(1, 0, 0, 1);
	fvec4 colorBottomRight = fvec4(1, 0, 0, 1);
	fvec4 colorTopLeft = fvec4(1, 0, 0, 1);
	fvec4 colorTopRight = fvec4(1, 0, 0, 1);

	Shape shapeData = ShapeMaker::makeRectangle(
		width,
		height,
		colorBottomLeft,
		colorBottomRight,
		colorTopLeft,
		colorTopRight);

	return new Enemy(
		vertex,
		fragment,
		shapeData,
		position,
		scaleVector,
		windowSize);
}

#pragma endregion

GameScene::~GameScene()
{
	delete this->background;
	delete this->gameObjects;
	delete this->gui;
}

void GameScene::updateGameObjects(float deltaTime)
{
	this->background->update(deltaTime);
	for (auto &&gameObject : *gameObjects)
	{
		gameObject->update(deltaTime);
	}
	for (auto &&temporaryGameObject : *temporaryGameObjects)
	{
		temporaryGameObject->update(deltaTime);
	}

	this->spawnProjectile();
	this->spawnEnemy(deltaTime);
	this->destroyTemporaryGameObjects();
}

void GameScene::renderScene(float currentTime)
{
	this->background->render(currentTime);
	this->renderGameObjects(currentTime);
	this->renderGui();
}

void GameScene::spawnProjectile()
{
	if (InputEvents::getButtonStates()->at(static_cast<size_t>(InputEventsType::SHOOT)))
	{
		this->temporaryGameObjects->push_back(GameScene::createProjectile(this->windowSize, this->spaceship->getBBCenter()));
		InputEvents::getButtonStates()->at(static_cast<size_t>(InputEventsType::SHOOT)) = false;
	}
}

void GameScene::spawnEnemy(float deltaTime)
{
	if (this->timeSinceLastEnemySpawn >= this->enemySpawnInterval)
	{
		this->temporaryGameObjects->push_back(GameScene::createEnemy(this->windowSize, this->enemySpawnPositions));
		this->timeSinceLastEnemySpawn = 0.0f;
		this->enemySpawnInterval = Random::getRandomFloat(this->enemySpawnIntervalRange.x, this->enemySpawnIntervalRange.y);
		cout << "Next enemy in: " << this->enemySpawnInterval << " seconds." << endl;
	}
	else
	{
		this->timeSinceLastEnemySpawn += deltaTime;
	}
}

void GameScene::destroyTemporaryGameObjects()
{
	for (size_t i = 0; i < this->temporaryGameObjects->size(); /* no increment here */)
	{
		ITemporaryGameObject *temporaryGameObject = this->temporaryGameObjects->at(i);

		if (temporaryGameObject->shouldDestroy())
		{
			this->temporaryGameObjects->erase(this->temporaryGameObjects->begin() + i);
			delete temporaryGameObject;
		}
		else
		{
			i++;
		}
	}
}

void GameScene::renderGameObjects(float currentTime)
{
	for (auto &&temporaryGameObject : *temporaryGameObjects)
	{
		temporaryGameObject->render(currentTime);
	}

	for (auto &&gameObject : *gameObjects)
	{
		gameObject->render(currentTime);
	}
}

void GameScene::renderGui()
{
	this->gui->drawGui();
}
