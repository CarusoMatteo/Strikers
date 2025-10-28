#pragma once

#include <vector>
#include "Mesh.h"
#include "./Game Objects/IGameObject.h"
#include "IGui.h"

using std::vector;

class Scene
{
public:
	Scene() = default;
	~Scene() = default;

	void renderScene();

private:
	Mesh *backgroundMesh;
	vector<IGameObject *> *gameObjects;
	IGui *gui;

	void buildBackgroundShader();
	void buildGameObjectShaders();

	void renderBackground();
	void renderGameObjects();
	void renderGui();
};
