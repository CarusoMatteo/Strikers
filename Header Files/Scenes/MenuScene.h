#pragma once
#include "IScene.h"

#include <vector>
#include <utility>
#include <glm/glm.hpp>

using glm::fvec2;
using glm::fvec3;
using glm::ivec2;
using std::pair;
using std::vector;

class Background;
class IGui;

class MenuScene : public IScene
{
public:
	MenuScene(ivec2 windowSize, fvec3 *clearColorRef, bool *startGame, float bestScore);
	~MenuScene();

	void updateGameObjects(float deltaTime);
	void renderScene(float currentTime);

private:
	Background *background;

	IGui *gui;
	ivec2 windowSize;

	static Background *createBackground(ivec2 windowSize);
	void renderGui();
};