#include "../Header Files/Stage.h"

Stage::Stage(SceneType startingScene, vec3 clearColor, string windowTitle)
{
	this->window = new Window(windowTitle);
	this->clearColor = clearColor;

	createScenes();
	this->changeScene(startingScene);
}

Stage::~Stage()
{
	delete scenes;
	delete window;
}

void Stage::createScenes()
{
	this->scenes = new vector<Scene *>();
	Scene *menuScene = new Scene(
		new Mesh(),
		new vector<IGameObject *>(),
		new MenuGui(&this->clearColor));
	Scene *gameScene = new Scene(
		new Mesh(),
		new vector<IGameObject *>(),
		new GameGui());
	scenes->at(static_cast<size_t>(SceneType::MENU)) = menuScene;
	scenes->at(static_cast<size_t>(SceneType::GAME)) = gameScene;
}

void Stage::renderCurrentScene(double currentTime, double deltaTime)
{
	scenes->at(static_cast<size_t>(currentScene))->renderScene(currentTime, deltaTime);
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
