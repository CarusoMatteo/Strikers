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
		MeshBuilder::buildPlane(
			".\\Shader Files\\Default\\DefaultVertex.glsl",
			".\\Shader Files\\Default\\DefaultFragment.glsl",
			true,
			this->window->getWindowSize(),
			fvec3(this->window->getWindowSize().x, this->window->getWindowSize().y, 1.0f),
			fvec4(0, 0, 1, 1),
			fvec4(1, 1, 1, 1),
			mat4(1.0f)),
		new vector<IGameObject *>(),
		new MenuGui(&this->clearColor));
	/*
	Scene *gameScene = new Scene(
		MeshBuilder::buildPlane(
			".\\Shader Files\\Background\\BackgroundVertex.glsl",
			".\\Shader Files\\Background\\BackgroundVertex.glsl",
			true, 2,
			this->window->getWindowSize(),
			fvec3(1.0f, 1.0f, 1.0f),
			fvec4(0, 0, 1, 1),
			fvec4(1, 1, 1, 1)),
		new vector<IGameObject *>(),
		new MenuGui(&this->clearColor));
	*/

	scenes->push_back(menuScene); // SceneType::MENU
								  // scenes->push_back(gameScene); // SceneType::GAME
}

void Stage::updateGameObjects(double deltaTime)
{
	scenes->at(static_cast<size_t>(currentScene))->updateGameObjects(deltaTime);
}

void Stage::renderCurrentScene(double currentTime)
{
	scenes->at(static_cast<size_t>(currentScene))->renderScene(currentTime);
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
