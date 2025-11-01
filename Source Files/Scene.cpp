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

void Scene::renderScene(double currentTime, double deltaTime)
{
	// TODO: Update time logic
	this->updateGameObjects(currentTime, deltaTime);
	this->backgroundMesh->render(0, currentTime);
	this->renderGameObjects(currentTime, deltaTime);
	this->renderGui();
}

void Scene::updateGameObjects(double currentTime, double deltaTime)
{
	for (auto &&gameObject : *gameObjects)
	{
		gameObject->update(currentTime, deltaTime);
	}
}

void Scene::renderGameObjects(double currentTime, double deltaTime)
{
	for (auto &&gameObject : *gameObjects)
	{
		gameObject->render();
	}
}

void Scene::renderGui()
{
	this->gui->drawGui();
}
