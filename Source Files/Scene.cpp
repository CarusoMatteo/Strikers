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
	this->renderBackground();
	this->renderGameObjects(currentTime, deltaTime);
	this->renderGui();
}

void Scene::renderBackground()
{
	this->backgroundMesh->render();
}

void Scene::renderGameObjects(double currentTime, double deltaTime)
{
	for (auto &&gameObject : *gameObjects)
	{
		gameObject->render(currentTime, deltaTime);
	}
}

void Scene::renderGui()
{
	this->gui->drawGui();
}
