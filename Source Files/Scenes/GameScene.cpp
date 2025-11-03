#include "../../Header Files/Scenes/GameScene.h"

#include "../../Header Files/Game Objects/Background.h"
#include "../../Header Files/Game Objects/Heart.h"
#include "../../Header Files/Game Objects/Spaceship.h"
#include "../../Header Files/Game Objects/Projectile.h"
#include "../../Header Files/Gui/MenuGui.h"
#include "../../Header Files/ShapeMaker.h"
#include "../../Header Files/InputEvents.h"

GameScene::GameScene(ivec2 windowSize, fvec3 *clearColorRef) : windowSize(windowSize)
{
	this->background = GameScene::createBackground(this->windowSize);
	Heart *heart = GameScene::createHeart(this->windowSize);
	this->spaceship = GameScene::createSpaceship(this->windowSize);

	this->gameObjects = new vector<IGameObject *>{
		heart,
		spaceship};
	this->projectiles = new vector<Projectile *>();

	this->gui = new MenuGui(clearColorRef);
}

Background *GameScene::createBackground(ivec2 windowSize)
{
	string vertex = ".\\Shader Files\\Background\\BackgroundVertex.glsl";
	string fragment = ".\\Shader Files\\Background\\BackgroundFragment.glsl";

	fvec3 position = fvec3(0, 0, 0);
	fvec3 scaleVector = fvec3(windowSize, 1);

	fvec4 colorBottomLeft = fvec4(1, 0, 0, 1);
	fvec4 colorBottomRight = fvec4(0, 1, 0, 1);
	fvec4 colorTopLeft = fvec4(0, 0, 1, 1);
	fvec4 colorTopRight = fvec4(1, 1, 1, 1);

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
		colorBorder);

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

	float width = 2;
	float height = 1;

	fvec3 position = fvec3(windowSize.x * 0.1, windowSize.y / 3.0, 0.0);
	fvec3 scaleVector = fvec3(100, 100, 1);

	fvec4 colorBottomLeft = fvec4(1, 0, 0, 1);
	fvec4 colorBottomRight = fvec4(0, 1, 0, 1);
	fvec4 colorTopLeft = fvec4(0, 0, 1, 1);
	fvec4 colorTopRight = fvec4(1, 1, 1, 1);

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
	fvec3 scaleVector = fvec3(100, 100, 1);

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
	for (auto &&projectile : *projectiles)
	{
		projectile->update(deltaTime);
	}

	if (InputEvents::getButtonStates()->at(static_cast<size_t>(InputEventsType::SHOOT)))
	{
		this->spawnProjectile();
		InputEvents::getButtonStates()->at(static_cast<size_t>(InputEventsType::SHOOT)) = false;
	}
	this->deleteOffScreenProjectiles();
}

void GameScene::renderScene(float currentTime)
{
	this->background->render(currentTime);
	this->renderGameObjects(currentTime);
	this->renderGui();
}

void GameScene::spawnProjectile()
{
	this->projectiles->push_back(GameScene::createProjectile(this->windowSize, this->spaceship->getPosition()));
}

void GameScene::deleteOffScreenProjectiles()
{
	for (size_t i = 0; i < this->projectiles->size(); /* no increment here */)
	{
		Projectile *projectile = this->projectiles->at(i);

		if (projectile->isOffScreen())
		{
			this->projectiles->erase(this->projectiles->begin() + i);
			delete projectile;
		}
		else
		{
			i++;
		}
	}
}

void GameScene::renderGameObjects(float currentTime)
{
	for (auto &&projectile : *projectiles)
	{
		projectile->render(currentTime);
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
