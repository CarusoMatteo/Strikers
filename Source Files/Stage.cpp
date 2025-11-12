#include "../Header Files/Stage.h"

#include "../Header Files/Gui/MenuGui.h"
#include "../Header Files/Gui/GameGui.h"
#include "../Header Files/Game Objects/Background.h"
#include "../Header Files/Game Objects/Heart.h"
#include "../Header Files/Game Objects/Spaceship.h"
#include "../Header Files/Scenes/GameScene.h"
#include "../Header Files/Scenes/MenuScene.h"
#include "../Header Files/Window.h"

Stage::Stage(SceneType startingScene, fvec3 clearColor, string windowTitle)
{
	this->window = new Window(windowTitle);
	this->clearColor = clearColor;

	createScenes();
	this->changeScene(startingScene);
}

Stage::~Stage()
{
	delete this->window;
}

void Stage::createScenes()
{
	this->scenes = Scenes{};

	scenes.at(static_cast<size_t>(SceneType::MENU)) =
		std::make_unique<MenuScene>(this->window->getWindowSize(), &clearColor);

	scenes.at(static_cast<size_t>(SceneType::GAME)) =
		std::make_unique<GameScene>(this->window->getWindowSize(), &clearColor);
}

void Stage::updateGameObjects(float deltaTime)
{
	scenes.at(static_cast<size_t>(currentScene))->updateGameObjects(deltaTime);
}

void Stage::renderCurrentScene(float currentTime)
{
	scenes.at(static_cast<size_t>(currentScene))->renderScene(currentTime);
}

void Stage::changeScene(SceneType nextScene)
{
	this->currentScene = nextScene;
}

void Stage::drawClearColor() const
{
	glClearColor(this->clearColor.x, this->clearColor.y, this->clearColor.z, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

bool Stage::shouldWindowClose()
{
	return this->window->shouldWindowClose();
}

void Stage::swapBuffers()
{
	this->window->swapBuffers();
}

void Stage::pollEvents()
{
	this->window->pollEvents();
}
