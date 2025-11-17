#pragma once

/**
 * @brief Interface for scenes.
 */
class IScene
{
public:
	virtual ~IScene() = default;
	/// @brief Updates all game objects in the scene.
	virtual void updateGameObjects(float deltaTime) = 0;
	/// @brief Renders all game objects in the scene.
	virtual void renderScene(float currentTime) = 0;
};