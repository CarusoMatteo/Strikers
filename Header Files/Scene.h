#pragma once

#include <vector>

using std::vector;

class IGui;
class IGameObject;
class Background;

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
