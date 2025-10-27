#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "Scene.h"
#include "SceneType.h"

using glm::vec4;
using std::vector;

class Stage
{
public:
	Stage() = default;
	~Stage() = default;

	void renderCurrentScene();
	void changeScene(SceneType sceneType);
	void drawClearColor();

private:
	vector<Scene *> *scenes;
	vec4 clearColor;
	SceneType currentScene;

	void createScenes();
};
