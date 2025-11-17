#pragma once
#include "IGameObject.h"

/**
 * @brief Interface for temporary game objects in the game.
 * Temporary game objects have a limited lifespan and can be deleted after certain conditions are met.
 */
class ITemporaryGameObject : public IGameObject
{
public:
	virtual ~ITemporaryGameObject() = default;
	virtual void update(float deltaTime) = 0;
	virtual void render(float currentTime) = 0;
	/**
	 * @brief Determines if the temporary game object should be deleted.
	 */
	virtual bool shouldDelete() = 0;
};
