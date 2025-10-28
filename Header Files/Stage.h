#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "Scene.h"
#include "SceneType.h"
#include "Window.h"

using glm::vec4;
using std::vector;

class Stage
{
public:
	Stage(SceneType startingScene, vec3 clearColor);
	~Stage() = default;

	void renderCurrentScene();
	void changeScene(SceneType nextScene);
	void drawClearColor() const;

	bool shouldWindowClose();
	void swapBuffers();
	void pollEvents();

private:
	vector<Scene *> *scenes;
	// clearColor's alpha is always 1.0f
	vec3 clearColor;
	SceneType currentScene;
	Window *window;

	void createScenes();
};
