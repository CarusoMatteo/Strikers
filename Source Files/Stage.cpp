#include "../Header Files/Stage.h"

#include "../Header Files/Gui/MenuGui.h"
#include "../Header Files/Gui/GameGui.h"
#include "../Header Files/Game Objects/Background.h"
#include "../Header Files/Game Objects/Heart.h"
#include "../Header Files/Game Objects/Spaceship.h"
#include "../Header Files/Scenes/GameScene.h"
#include "../Header Files/Scenes/MenuScene.h"
#include "../Header Files/Window.h"

Stage::Stage(SceneType startingScene, fvec3 clearColor, string windowTitle, bool *startGame)
{
	this->window = new Window(windowTitle);
	this->clearColor = clearColor;
	this->changeScene(startingScene, startGame);
}

Stage::~Stage()
{
	delete this->window;
}

void Stage::createMenuScene(bool *startGame)
{
	this->menuScene = std::make_unique<MenuScene>(this->window->getWindowSize(), &clearColor, startGame, this->bestScore);
}

void Stage::createGameScene(bool *startGame)
{
	this->gameScene = std::make_unique<GameScene>(this->window->getWindowSize(), &clearColor, startGame);
}

void Stage::updateGameObjects(float deltaTime)
{
	switch (currentScene)
	{
	case SceneType::MENU:
		static_cast<IScene *>(this->menuScene.get())->updateGameObjects(deltaTime);
		break;
	case SceneType::GAME:
		static_cast<IScene *>(this->gameScene.get())->updateGameObjects(deltaTime);
		break;
	}
}

void Stage::renderCurrentScene(float currentTime)
{
	switch (currentScene)
	{
	case SceneType::MENU:
		static_cast<IScene *>(this->menuScene.get())->renderScene(currentTime);
		break;
	case SceneType::GAME:
		static_cast<IScene *>(this->gameScene.get())->renderScene(currentTime);
		break;
	}
}

void Stage::changeScene(SceneType nextScene, bool *startGame)
{
	switch (nextScene)
	{
	case SceneType::MENU:
	{
		float score = gameScene ? static_cast<GameScene *>(this->gameScene.get())->getScore() : 0.0f;
		if (score > this->bestScore)
		{
			this->bestScore = score;
		}
		this->createMenuScene(startGame);
	}
	break;
	case SceneType::GAME:
		this->createGameScene(startGame);
	}

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
