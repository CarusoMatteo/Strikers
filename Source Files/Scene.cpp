#include "../Header Files/Scene.h"

Scene::Scene(Mesh *backgroundMesh, vector<IGameObject *> *gameObjects, IGui *gui)
{
	this->backgroundMesh = backgroundMesh;
	this->gameObjects = gameObjects;
	this->gui = gui;
}

Scene::~Scene()
{
	delete this->backgroundMesh;
	delete this->gameObjects;
	delete this->gui;
}

void Scene::updateGameObjects(double deltaTime)
{
	for (auto &&gameObject : *gameObjects)
	{
		gameObject->update(deltaTime);
	}
}

void Scene::renderScene(double currentTime)
{
	this->backgroundMesh->render(currentTime);
	this->renderGameObjects(currentTime);
	this->renderGui();
}

void Scene::renderGameObjects(double currentTime)
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
