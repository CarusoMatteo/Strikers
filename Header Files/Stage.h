#pragma once

#include <string>
#include <array>
#include <memory>
#include <glm/glm.hpp>

#include "../Header Files/Scenes/SceneType.h"

using glm::fmat4;
using glm::fvec3;
using glm::fvec4;
using std::array;
using std::string;

class IScene;
class Window;

using Scenes = std::array<std::unique_ptr<IScene>, static_cast<size_t>(SceneType::count)>;

/**
 * @brief Manages different scenes of the game (menu, gameplay, etc.), handles scene transitions, updates, and rendering.
 * Creates and destroys scenes and manages the main window.
 */
class Stage
{
public:
	Stage(SceneType startingScene, fvec3 clearColor, string windowTitle, bool *startGame);
	~Stage();

	/// @brief Updates all game objects in the current scene.
	void updateGameObjects(float deltaTime);
	/// @brief Renders the current scene.
	void renderCurrentScene(float currentTime);
	/// @brief Changes the current scene to the specified next scene.
	void changeScene(SceneType nextScene, bool *startGame);
	/// @brief Draws the clear color.
	void drawClearColor() const;

	/// @returns if the window should close.
	bool shouldWindowClose();
	/// @brief Swaps the front and back buffers of the window.
	void swapBuffers();
	/// @brief Polls for and processes events.
	void pollEvents();

private:
	std::unique_ptr<IScene> menuScene;
	std::unique_ptr<IScene> gameScene;
	/// @brief Color used to clear the screen before rendering each frame. Its alpha is always 1.0f.
	fvec3 clearColor;
	SceneType currentScene;
	Window *window;

	float bestScore = 0.0f;

	void createMenuScene(bool *startGame);
	void createGameScene(bool *startGame);
};
