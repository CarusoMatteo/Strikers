#include "../../Header Files/Scenes/MenuScene.h"

#include "../../Header Files/Game Objects/Background.h"
#include "../../Header Files/Gui/MenuGui.h"
#include "../../Header Files/ShapeMaker.h"

MenuScene::MenuScene(ivec2 windowSize, fvec3 *clearColorRef, bool *startGame, float bestScore) : windowSize(windowSize)
{
	this->background = MenuScene::createBackground(this->windowSize);
	this->gui = new MenuGui(clearColorRef, startGame, bestScore);
}

MenuScene::~MenuScene()
{
	delete this->background;
	delete this->gui;
}

Background *MenuScene::createBackground(ivec2 windowSize)
{
	string vertex = ".\\Shader Files\\Background\\BackgroundVertex.glsl";
	string fragment = ".\\Shader Files\\Background\\STBackgroundFragment.glsl";
	// string fragment = ".\\Shader Files\\Background\\BackgroundFragment.glsl";

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

void MenuScene::updateGameObjects(float deltaTime)
{
}

void MenuScene::renderScene(float currentTime)
{
	this->background->render(currentTime);
	this->renderGui();
}

void MenuScene::renderGui()
{
	this->gui->drawGui();
}
