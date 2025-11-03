#include "../Header Files/Scene.h"

#include "../Header Files/Game Objects/Background.h"
#include "../Header Files/Gui/IGui.h"

Scene::Scene(Background *background, vector<IGameObject *> *gameObjects, IGui *gui) : background(background), gameObjects(gameObjects), gui(gui)
{
}

Scene::~Scene()
{
	delete this->background;
	delete this->gameObjects;
	delete this->gui;
}

void Scene::updateGameObjects(float deltaTime)
{
	this->background->update(deltaTime);
	for (auto &&gameObject : *gameObjects)
	{
		gameObject->update(deltaTime);
	}
}

void Scene::renderScene(float currentTime)
{
	this->background->render(currentTime);
	this->renderGameObjects(currentTime);
	this->renderGui();
}

void Scene::renderGameObjects(float currentTime)
{
	for (auto &&gameObject : *gameObjects)
	{
		gameObject->render(currentTime);
	}
}

void Scene::renderGui()
{
	this->gui->drawGui();
}
