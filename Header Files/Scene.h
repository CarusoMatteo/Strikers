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

	void updateGameObjects(double deltaTime);
	void renderScene(double currentTime);

private:
	Mesh *backgroundMesh;
	vector<IGameObject *> *gameObjects;
	IGui *gui;

	void renderGameObjects(double currentTime);
	void renderGui();
};
