#include "../../Header Files/Scenes/GameScene.h"

#include "../../Header Files/Game Objects/Background.h"
#include "../../Header Files/Game Objects/Heart.h"
#include "../../Header Files/Game Objects/Spaceship.h"
#include "../../Header Files/Gui/MenuGui.h"
#include "../../Header Files/MeshBuilder.h"

GameScene::GameScene(ivec2 windowSize, fvec3 *clearColorRef)
{
	this->background = &GameScene::createBackground(windowSize);
	Heart heart = GameScene::createHeart(windowSize);
	Spaceship spaceship = GameScene::createSpaceship(windowSize);

	this->gameObjects = new vector<IGameObject>{
		heart,
		spaceship};
	this->gui = new MenuGui(clearColorRef);
}

Background GameScene::createBackground(ivec2 windowSize)
{
	string vertex = ".\\Shader Files\\Background\\BackgroundVertex.glsl";
	string fragment = ".\\Shader Files\\Background\\BackgroundFragment.glsl";

	fvec3 position = fvec3(0, 0, 0);
	fvec3 scaleVector = fvec3(windowSize.x, windowSize.y, 1);

	fvec4 colorBottomLeft = fvec4(1, 0, 0, 1);
	fvec4 colorBottomRight = fvec4(0, 1, 0, 1);
	fvec4 colorTopLeft = fvec4(0, 0, 1, 1);
	fvec4 colorTopRight = fvec4(1, 1, 1, 1);

	return Background(MeshBuilder::buildBackgroundMesh(
		vertex,
		fragment,
		true,
		windowSize,
		position,
		scaleVector,
		colorBottomLeft,
		colorBottomRight,
		colorTopLeft,
		colorTopRight,
		fmat4(1)));
}

Heart GameScene::createHeart(ivec2 windowSize)
{
	string vertex = ".\\Shader Files\\Heart\\HeartVertex.glsl";
	string fragment = ".\\Shader Files\\Heart\\HeartFragment.glsl";

	int numberOfTriangles = 100;
	fvec2 center = fvec2(0, 0);
	fvec2 radius = fvec2(1, 1);

	fvec3 position = fvec3(windowSize.x * 0.1, windowSize.y / 3.0, 0.0);
	fvec3 scaleVector = fvec3(5, 5, 1);

	fvec4 colorCenter = fvec4(1, 0, 0, 1);
	fvec4 colorBorder = fvec4(0.5f, 0, 0, 1);

	return Heart(MeshBuilder::buildHeartBB(
		vertex,
		fragment,
		true,
		numberOfTriangles,
		center,
		radius,
		windowSize,
		position,
		scaleVector,
		colorCenter,
		colorBorder,
		fmat4(1)));
}

Spaceship GameScene::createSpaceship(ivec2 windowSize)
{
	string vertex = ".\\Shader Files\\Heart\\HeartVertex.glsl";
	string fragment = ".\\Shader Files\\Heart\\HeartFragment.glsl";

	float width = 2;
	float height = 1;

	fvec3 position = fvec3(windowSize.x * 0.1, windowSize.y / 3.0, 0.0);
	fvec3 scaleVector = fvec3(100, 100, 1);

	fvec4 colorBottomLeft = fvec4(1, 0, 0, 1);
	fvec4 colorBottomRight = fvec4(0, 1, 0, 1);
	fvec4 colorTopLeft = fvec4(0, 0, 1, 1);
	fvec4 colorTopRight = fvec4(1, 1, 1, 1);

	return Spaceship(MeshBuilder::buildRectangleBB(
		".\\Shader Files\\Default\\DefaultVertex.glsl",
		".\\Shader Files\\Default\\DefaultFragment.glsl",
		true,
		width,
		height,
		windowSize,
		position,
		scaleVector,
		colorTopLeft,
		colorTopRight,
		colorBottomLeft,
		colorBottomRight,
		fmat4(1)));
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
		gameObject.update(deltaTime);
	}
}

void GameScene::renderScene(float currentTime)
{
	this->background->render(currentTime);
	this->renderGameObjects(currentTime);
	this->renderGui();
}

void GameScene::renderGameObjects(float currentTime)
{
	for (auto &&gameObject : *gameObjects)
	{
		gameObject.render(currentTime);
	}
}

void GameScene::renderGui()
{
	this->gui->drawGui();
}
