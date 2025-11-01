#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "Gui/MenuGui.h"
#include "Gui/GameGui.h"
#include "Scene.h"
#include "SceneType.h"
#include "Window.h"
#include "MeshBuilder.h"

using glm::vec4;
using std::string;
using std::vector;

class Stage
{
public:
	Stage(SceneType startingScene, vec3 clearColor, string windowTitle);
	~Stage();

	void updateGameObjects(double deltaTime);
	void renderCurrentScene(double currentTime);
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
