#pragma once

#include <vector>
#include "Mesh.h"
#include "./Game Objects/IGameObject.h"
#include "./Gui/IGui.h"

using std::vector;

class Scene
{
public:
	Scene(Mesh *backgroundMesh, vector<IGameObject *> *gameObjects, IGui *gui);
	~Scene();

	void renderScene(double currentTime, double deltaTime);

private:
	Mesh *backgroundMesh;
	vector<IGameObject *> *gameObjects;
	IGui *gui;

	void updateGameObjects(double currentTime, double deltaTime);
	void renderGameObjects(double currentTime, double deltaTime);
	void renderGui();
};
