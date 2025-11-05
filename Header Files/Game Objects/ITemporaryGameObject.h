#pragma once
#include "IGameObject.h"

class ITemporaryGameObject : public IGameObject
{
public:
	virtual ~ITemporaryGameObject() = default;
	virtual void update(float deltaTime) = 0;
	virtual void render(float currentTime) = 0;
	virtual bool shouldDestroy() = 0;
};
