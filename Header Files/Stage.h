#pragma once

#include <string>
#include <array>
#include <glm/glm.hpp>

#include "Gui/MenuGui.h"
#include "Gui/GameGui.h"
#include "Scene.h"
#include "SceneType.h"
#include "Window.h"
#include "MeshBuilder.h"

using glm::vec4;
using std::array;
using std::string;
using Scenes = std::array<Scene *, static_cast<size_t>(SceneType::count)>;

class Stage
{
public:
	Stage(SceneType startingScene, vec3 clearColor, string windowTitle);
	~Stage();

	void updateGameObjects(float deltaTime);
	void renderCurrentScene(float currentTime);
	void changeScene(SceneType nextScene);
	void drawClearColor() const;

	bool shouldWindowClose();
	void swapBuffers();
	void pollEvents();

private:
	Scenes *scenes;
	// clearColor's alpha is always 1.0f
	vec3 clearColor;
	SceneType currentScene;
	Window *window;

	void createScenes();
};
