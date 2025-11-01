#pragma once

#include <vector>
#include "Mesh.h"
#include "./Game Objects/IGameObject.h"
#include "./Game Objects/Background.h"
#include "./Gui/IGui.h"

using std::vector;

class Scene
{
public:
	Scene(Background *background, vector<IGameObject *> *gameObjects, IGui *gui);
	~Scene();

	void updateGameObjects(float deltaTime);
	void renderScene(float currentTime);

private:
	Background *background;
	vector<IGameObject *> *gameObjects;
	IGui *gui;

	void renderGameObjects(float currentTime);
	void renderGui();
};
