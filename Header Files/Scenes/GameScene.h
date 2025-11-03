#pragma once
#include "Scene.h"

#include <vector>
#include <utility>
#include <glm/glm.hpp>

using glm::fvec3;
using glm::ivec2;
using std::pair;
using std::vector;

class Background;
class Heart;
class Spaceship;
class IGameObject;
class IGui;

class GameScene : public Scene
{
public:
	GameScene(ivec2 windowSize, fvec3 *clearColorRef);
	~GameScene();

	void updateGameObjects(float deltaTime);
	void renderScene(float currentTime);

private:
	Background *background;
	vector<IGameObject *> *gameObjects;
	IGui *gui;

	static Background *createBackground(ivec2 windowSize);
	static Heart *createHeart(ivec2 windowSize);
	static Spaceship *createSpaceship(ivec2 windowSize);
	void renderGameObjects(float currentTime);

	void renderGui();
};