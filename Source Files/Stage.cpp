#include "../Header Files/Stage.h"

Stage::Stage(SceneType startingScene, vec3 clearColor, string windowTitle)
{
	this->window = new Window(windowTitle);
	this->clearColor = clearColor;

	createScenes();
	this->changeScene(startingScene);
}

void Stage::createScenes()
{
	this->scenes = new vector<Scene *>();
	Scene *menuScene = new Scene();
	Scene *gameScene = new Scene();
	scenes->at(SceneType::MENU) = menuScene;
	scenes->at(SceneType::GAME) = gameScene;
}

void Stage::renderCurrentScene()
{
	scenes->at(currentScene)->renderScene();
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
