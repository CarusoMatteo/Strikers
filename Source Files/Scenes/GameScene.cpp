#include "../../Header Files/Scenes/GameScene.h"

#include "../../Header Files/Game Objects/Background.h"
#include "../../Header Files/Game Objects/Heart.h"
#include "../../Header Files/Game Objects/Spaceship.h"
#include "../../Header Files/Game Objects/Projectile.h"
#include "../../Header Files/Game Objects/ProjectileExplosion.h"
#include "../../Header Files/Game Objects/Enemy.h"
#include "../../Header Files/Game Objects/EnemyExplosion.h"
#include "../../Header Files/Gui/GameGui.h"
#include "../../Header Files/Gui/GameOverGui.h"
#include "../../Header Files/ShapeMaker.h"
#include "../../Header Files/HermiteCurveMaker.h"
#include "../../Header Files/InputEvents.h"
#include "../../Header Files/Random.h"
#include "../../Header Files/MeshCurveBB.h"

GameScene::GameScene(ivec2 windowSize, fvec3 *clearColorRef, bool *startGame) : windowSize(windowSize), startGame(startGame)
{
	this->background = GameScene::createBackground(this->windowSize);
	this->spaceship = GameScene::createSpaceship(this->windowSize);
	Heart *heart = GameScene::createHeart(this->windowSize, this->spaceship->getHealthRef());

	this->gameObjects = new vector<IGameObject *>{
		heart,
		spaceship};
	this->temporaryGameObjects = new vector<ITemporaryGameObject *>();

	this->gui = new GameGui(clearColorRef, &this->score);

	this->enemySpawnPositions = {
		fvec3(windowSize.x * 1.1f, windowSize.y * 0.2f, 0.0f),
		fvec3(windowSize.x * 1.1f, windowSize.y * 0.4f, 0.0f),
		fvec3(windowSize.x * 1.1f, windowSize.y * 0.6f, 0.0f),
		fvec3(windowSize.x * 1.1f, windowSize.y * 0.8f, 0.0f)};
}

#pragma region Game Object Creators

Background *GameScene::createBackground(ivec2 windowSize)
{
	string vertex = ".\\Shader Files\\Background\\BackgroundVertex.glsl";
	// string fragment = ".\\Shader Files\\Background\\BackgroundFragment.glsl";
	string fragment = ".\\Shader Files\\Background\\STBackgroundFragment.glsl";

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

Heart *GameScene::createHeart(ivec2 windowSize, float *spaceshipHealthRef)
{
	string vertex = ".\\Shader Files\\Heart\\HeartVertex.glsl";
	string fragment = ".\\Shader Files\\Heart\\HeartFragment.glsl";

	int numberOfTriangles = 100;
	fvec2 radius = fvec2(1, 1);

	fvec3 position = fvec3(windowSize.x * 0.9f, windowSize.y * 0.9f, 0.0);
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
		windowSize,
		spaceshipHealthRef);
}

Spaceship *GameScene::createSpaceship(ivec2 windowSize)
{
	string vertex = ".\\Shader Files\\Spaceship\\SpaceshipVertex.glsl";
	string fragment = ".\\Shader Files\\Spaceship\\SpaceshipFragment.glsl";

	int numberOfTriangles = 200;

	fvec3 position = fvec3(windowSize.x * 0.1, windowSize.y / 2.0, 0.0);
	fvec3 scaleVector = fvec3(125, 120, 1);

	fvec4 colorTop = fvec4(1, 1, 1, 1);
	fvec4 colorBottom = fvec4(0, 1, 1, 1);

	Shape shapeData = ShapeMaker::makeHermitCurve(
		"Curves/spaceship.txt",
		numberOfTriangles,
		colorTop,
		colorBottom,
		true);

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

	int numberOfTriangles = 200;

	fvec3 position = spaceshipPosition;
	fvec3 scaleVector = fvec3(50, 50, 1);

	fvec4 colorTop = fvec4(1, 1, 1, 1);
	fvec4 colorBottom = fvec4(1, 1, 1, 1);

	Shape shapeData = ShapeMaker::makeHermitCurve(
		"Curves/projectile.txt",
		numberOfTriangles,
		colorTop,
		colorBottom,
		true);

	return new Projectile(
		vertex,
		fragment,
		shapeData,
		position,
		scaleVector,
		windowSize);
}

ProjectileExplosion *GameScene::createProjectileExplosion(ivec2 windowSize, fvec3 spawnPosition)
{
	string vertex = ".\\Shader Files\\Explosion\\ExplosionVertex.glsl";
	string fragment = ".\\Shader Files\\Explosion\\ExplosionFragment.glsl";

	float sideLenght = 1;

	int numberOfTriangles = 100;
	fvec2 radius = fvec2(1, 1);

	fvec3 position = spawnPosition;
	fvec3 scaleVector = fvec3(50, 50, 1);

	fvec4 colorCenter = fvec4(1, 1, 0, 1);
	fvec4 colorBorder = fvec4(1, 1, 1, 1);

	Shape shapeData = ShapeMaker::makeCircle(
		numberOfTriangles,
		radius,
		colorCenter,
		colorBorder,
		false);

	return new ProjectileExplosion(
		vertex,
		fragment,
		shapeData,
		position,
		scaleVector,
		windowSize);
}

Enemy *GameScene::createEnemy(ivec2 windowSize, vector<fvec3> enemySpawnPositions)
{
	string vertex = ".\\Shader Files\\Enemy\\EnemyVertex.glsl";
	string fragment = ".\\Shader Files\\Enemy\\EnemyFragment.glsl";

	int numberOfTriangles = 200;

	fvec3 position = enemySpawnPositions[Random::getRandomInt(0, static_cast<int>(enemySpawnPositions.size()))];
	float scaleX = Random::getRandomFloat(100, 200);
	float scaleY = Random::getRandomFloat(100, 200);
	fvec3 scaleVector = fvec3(scaleX, scaleY, 1);
	float rotationDegrees = 0.0f;
	// float rotationDegrees = Random::getRandomFloat(0, 360);

	fvec4 colorTop = fvec4(1, 1, 1, 1);
	fvec4 colorBottom = fvec4(1, 0, 0, 1);

	Shape shapeData = ShapeMaker::makeHermitCurve(
		"Curves/enemy.txt",
		numberOfTriangles,
		colorTop,
		colorBottom,
		true);

	return new Enemy(
		vertex,
		fragment,
		shapeData,
		position,
		rotationDegrees,
		scaleVector,
		windowSize);
}

EnemyExplosion *GameScene::createEnemyExplosion(ivec2 windowSize, fvec3 spawnPosition, fvec3 sizeWorld)
{
	string vertex = ".\\Shader Files\\Explosion\\ExplosionVertex.glsl";
	string fragment = ".\\Shader Files\\Explosion\\ExplosionFragment.glsl";

	float width = 1;
	float height = 0.5f;

	fvec3 positionTop = spawnPosition + fvec3(0, sizeWorld.y / 2, 0);
	fvec3 positionBottom = spawnPosition;
	float rotationDegreesTop = 0.0f;
	float rotationDegreesBottom = 0.0f;
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
		colorTopRight,
		false);

	return new EnemyExplosion(
		vertex,
		fragment,
		shapeData,
		positionTop,
		positionBottom,
		rotationDegreesTop,
		rotationDegreesBottom,
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
	if (!this->spaceship->isAlive())
	{
		if (!dynamic_cast<GameOverGui *>(this->gui))
		{
			IGui *oldGui = this->gui;
			this->gui = new GameOverGui(oldGui->getClearColorRef(), this->startGame);
			delete oldGui;
		}
		// Update for one last time
		for (auto &&gameObject : *gameObjects)
		{
			gameObject->update(deltaTime);
		}

		return;
	}

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
	this->checkCollisions();
	this->deleteTemporaryGameObjects();
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
		this->temporaryGameObjects->push_back(GameScene::createProjectile(this->windowSize, this->spaceship->getProjectileSpawnPosition()));
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
		// cout << "Next enemy in: " << this->enemySpawnInterval << " seconds." << endl;
	}
	else
	{
		this->timeSinceLastEnemySpawn += deltaTime;
	}
}

void GameScene::deleteTemporaryGameObjects()
{
	for (size_t i = 0; i < this->temporaryGameObjects->size(); /* no increment here */)
	{
		ITemporaryGameObject *temporaryGameObject = this->temporaryGameObjects->at(i);

		if (temporaryGameObject->shouldDelete())
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

void GameScene::checkCollisions()
{
	// Check collision of player vs enemies
	for (size_t i = 0; i < this->temporaryGameObjects->size(); /* no increment here */)
	{
		Enemy *enemy = dynamic_cast<Enemy *>(this->temporaryGameObjects->at(i));
		if (enemy && MeshBB::checkCollision(this->spaceship->getMesh(), enemy->getMesh()))
		{
			this->spaceship->takeDamage();
			this->temporaryGameObjects->erase(this->temporaryGameObjects->begin() + i);
			delete enemy;
			continue;
		}
		i++;
	}

	// Check collision of enemies vs projectiles
	for (size_t i = 0; i < this->temporaryGameObjects->size(); i++)
	{
		Enemy *enemy = dynamic_cast<Enemy *>(this->temporaryGameObjects->at(i));
		if (enemy)
		{
			for (size_t j = 0; j < this->temporaryGameObjects->size(); j++)
			{
				Projectile *projectile = dynamic_cast<Projectile *>(this->temporaryGameObjects->at(j));
				if (projectile && MeshBB::checkCollision(enemy->getMesh(), projectile->getMesh()))
				{
					replaceEnemy(i);
					replaceProjectile(j);
					break;
				}
			}
		}
	}
}

void GameScene::replaceEnemy(size_t position)
{
	Enemy *enemy = dynamic_cast<Enemy *>(this->temporaryGameObjects->at(position));
	this->temporaryGameObjects->at(position) = GameScene::createEnemyExplosion(this->windowSize, enemy->getMesh()->getPosition(), enemy->getSizeWorld());
	this->score += Parameters::pointMultiplier * enemy->getScore();
	delete enemy;
}

void GameScene::replaceProjectile(size_t position)
{
	Projectile *projectile = dynamic_cast<Projectile *>(this->temporaryGameObjects->at(position));
	this->temporaryGameObjects->at(position) = GameScene::createProjectileExplosion(this->windowSize, projectile->getMesh()->getPosition());
	delete projectile;
}