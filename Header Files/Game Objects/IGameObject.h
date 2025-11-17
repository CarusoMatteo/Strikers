#pragma once

/**
 * @brief Interface for all game objects in the game.
 */
class IGameObject
{
public:
	virtual ~IGameObject() = default;

	/**
	 * @brief Updates the game object's state.
	 * @param deltaTime
	 */
	virtual void update(float deltaTime) = 0;
	/**
	 * @brief Renders the game object.
	 * @param currentTime
	 */
	virtual void render(float currentTime) = 0;
};
