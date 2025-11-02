#pragma once

#include <string>
#include <array>
#include <memory>
#include <glm/glm.hpp>

#include "Gui/MenuGui.h"
#include "Gui/GameGui.h"
#include "./Game Objects/Heart.h"
#include "Scene.h"
#include "SceneType.h"
#include "Window.h"
#include "MeshBuilder.h"

using glm::fmat4;
using glm::fvec3;
using glm::fvec4;
using std::array;
using std::string;
using Scenes = std::array<std::unique_ptr<Scene>, static_cast<size_t>(SceneType::count)>;

class Stage
{
public:
	Stage(SceneType startingScene, fvec3 clearColor, string windowTitle);
	~Stage();

	void updateGameObjects(float deltaTime);
	void renderCurrentScene(float currentTime);
	void changeScene(SceneType nextScene);
	void drawClearColor() const;

	bool shouldWindowClose();
	void swapBuffers();
	void pollEvents();

private:
	Scenes scenes;
	// clearColor's alpha is always 1.0f
	fvec3 clearColor;
	SceneType currentScene;
	Window *window;

	void createScenes();
};
